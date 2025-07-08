
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
	TexMetadata metadata;    // �摜�̕t�����
	ScratchImage image;      // �摜�{��

	// std::string �� std::wstring �ϊ�
	std::wstring wFileName(fileName.begin(), fileName.end());

	// �摜�t�@�C����ǂݍ���
	HRESULT hr = LoadFromWICFile(wFileName.c_str(), WIC_FLAGS_NONE, &metadata, image);
	if (FAILED(hr))
	{
		return hr;
	}

	// �T���v���[�X�e�[�g�̐ݒ�
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

	// �V�F�[�_�[���\�[�X�r���[�̍쐬
	hr = CreateShaderResourceView(
		Direct3D::pDevice,
		image.GetImages(),
		image.GetImageCount(),
		metadata,
		&pSRV_);
	if (FAILED(hr))
	{
		// �T���v���[�X�e�[�g�͍쐬�ς݂Ȃ̂ŉ��
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
