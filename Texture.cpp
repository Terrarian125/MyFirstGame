
#include "Texture.h"
#include "Direct3D.h"
#include <DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

using namespace DirectX;

Texture::Texture()
	: pSampler_(nullptr), pSRV_(nullptr)
{
}

Texture::~Texture()
{
	Release();
}

HRESULT Texture::Load(std::string fileName)
{
	TexMetadata metadata;    // 画像の付属情報
	ScratchImage image;      // 画像本体

	// std::string → std::wstring 変換
	std::wstring wFileName(fileName.begin(), fileName.end());

	// 画像ファイルを読み込む
	HRESULT hr = LoadFromWICFile(wFileName.c_str(), WIC_FLAGS_NONE, &metadata, image);
	if (FAILED(hr))
	{
		return hr;
	}

	// サンプラーステートの設定
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = Direct3D::pDevice->CreateSamplerState(&samplerDesc, &pSampler_);
	if (FAILED(hr))
	{
		return hr;
	}

	// シェーダーリソースビューの作成
	hr = CreateShaderResourceView(
		Direct3D::pDevice,
		image.GetImages(),
		image.GetImageCount(),
		metadata,
		&pSRV_);
	if (FAILED(hr))
	{
		// サンプラーステートは作成済みなので解放
		if (pSampler_)
		{
			pSampler_->Release();
			pSampler_ = nullptr;
		}
		return hr;
	}

	return S_OK;
}

void Texture::Release()
{
	if (pSampler_)
	{
		pSampler_->Release();
		pSampler_ = nullptr;
	}
	if (pSRV_)
	{
		pSRV_->Release();
		pSRV_ = nullptr;
	}
}

ID3D11SamplerState* Texture::GetSampler()
{
	return pSampler_;
}

ID3D11ShaderResourceView* Texture::GetSRV()
{
	return pSRV_;
}
