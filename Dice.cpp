#include "Dice.h"
#include "Direct3D.h"
#include "Camera.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include "Quad.h"
using namespace DirectX;

Dice::Dice()
    : vertexBuffer_(nullptr), constantBuffer_(nullptr), texture_(nullptr)
{
}

Dice::~Dice()
{
    //if (vertexBuffer_) { vertexBuffer_->Release(); vertexBuffer_ = nullptr; }
    //if (constantBuffer_) { constantBuffer_->Release(); constantBuffer_ = nullptr; }
    //if (texture_) { texture_->Release(); delete texture_; texture_ = nullptr; }
}

HRESULT Dice::Initialize()
{
    HRESULT hr = S_OK;

    // テクスチャのロード
    texture_ = new Texture();
    hr = texture_->Load("Assets/Dice.png");
    if (FAILED(hr)) return hr;

    // 頂点バッファの作成
    hr = CreateVertexBuffer();
    if (FAILED(hr)) return hr;

    // 定数バッファの作成
    D3D11_BUFFER_DESC cbd = {};
    cbd.Usage = D3D11_USAGE_DEFAULT;
    cbd.ByteWidth = sizeof(XMMATRIX);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    hr = Direct3D::pDevice->CreateBuffer(&cbd, nullptr, &constantBuffer_);
    if (FAILED(hr)) return hr;

    return S_OK;
}

HRESULT Dice::CreateVertexBuffer()
{
    Vertex vertices[36]; // 6面 × 2三角形 × 3頂点 = 36頂点

    const float texWidth = 512.0f;
    const float texHeight = 256.0f;
    const float faceWidthUV = 128.0f / texWidth;  // 0.25
    const float faceHeightUV = 128.0f / texHeight; // 0.5

    struct UVOffset { float u; float v; };
    UVOffset uvOffsets[6] = {
        { 0.0f * faceWidthUV, 0.0f * faceHeightUV }, // 面1 (上段左端)
        { 1.0f * faceWidthUV, 0.0f * faceHeightUV }, // 面2
        { 2.0f * faceWidthUV, 0.0f * faceHeightUV }, // 面3
        { 3.0f * faceWidthUV, 0.0f * faceHeightUV }, // 面4
        { 0.0f * faceWidthUV, 1.0f * faceHeightUV }, // 面5 (下段左端)
        { 1.0f * faceWidthUV, 1.0f * faceHeightUV }  // 面6
    };

    auto SetFaceVertices = [&](int faceIndex, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3 v3)
        {
            int base = faceIndex * 6;
            float uOff = uvOffsets[faceIndex].u;
            float vOff = uvOffsets[faceIndex].v;

            // 左上、右上、左下、右上、右下、左下 の順で三角形2つ作る
            vertices[base + 0] = { v0, XMFLOAT2(uOff, vOff) };
            vertices[base + 1] = { v1, XMFLOAT2(uOff + faceWidthUV, vOff) };
            vertices[base + 2] = { v2, XMFLOAT2(uOff, vOff + faceHeightUV) };
            vertices[base + 3] = { v1, XMFLOAT2(uOff + faceWidthUV, vOff) };
            vertices[base + 4] = { v3, XMFLOAT2(uOff + faceWidthUV, vOff + faceHeightUV) };
            vertices[base + 5] = { v2, XMFLOAT2(uOff, vOff + faceHeightUV) };
        };

    // 6面の頂点座標
    SetFaceVertices(0, // 前面 (Z+)
        XMFLOAT3(-0.5f, 0.5f, 0.5f),
        XMFLOAT3(0.5f, 0.5f, 0.5f),
        XMFLOAT3(-0.5f, -0.5f, 0.5f),
        XMFLOAT3(0.5f, -0.5f, 0.5f));

    SetFaceVertices(1, // 背面 (Z-)
        XMFLOAT3(0.5f, 0.5f, -0.5f),
        XMFLOAT3(-0.5f, 0.5f, -0.5f),
        XMFLOAT3(0.5f, -0.5f, -0.5f),
        XMFLOAT3(-0.5f, -0.5f, -0.5f));

    SetFaceVertices(2, // 上面 (Y+)
        XMFLOAT3(-0.5f, 0.5f, -0.5f),
        XMFLOAT3(0.5f, 0.5f, -0.5f),
        XMFLOAT3(-0.5f, 0.5f, 0.5f),
        XMFLOAT3(0.5f, 0.5f, 0.5f));

    SetFaceVertices(3, // 底面 (Y-)
        XMFLOAT3(-0.5f, -0.5f, 0.5f),
        XMFLOAT3(0.5f, -0.5f, 0.5f),
        XMFLOAT3(-0.5f, -0.5f, -0.5f),
        XMFLOAT3(0.5f, -0.5f, -0.5f));

    SetFaceVertices(4, // 右面 (X+)
        XMFLOAT3(0.5f, 0.5f, 0.5f),
        XMFLOAT3(0.5f, 0.5f, -0.5f),
        XMFLOAT3(0.5f, -0.5f, 0.5f),
        XMFLOAT3(0.5f, -0.5f, -0.5f));

    SetFaceVertices(5, // 左面 (X-)
        XMFLOAT3(-0.5f, 0.5f, -0.5f),
        XMFLOAT3(-0.5f, 0.5f, 0.5f),
        XMFLOAT3(-0.5f, -0.5f, -0.5f),
        XMFLOAT3(-0.5f, -0.5f, 0.5f));

    // バッファ作成
    D3D11_BUFFER_DESC bd{};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Vertex) * 36;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA sd{};
    sd.pSysMem = vertices;

    HRESULT hr = Direct3D::pDevice->CreateBuffer(&bd, &sd, &vertexBuffer_);
    return hr;
}

void Dice::Draw(XMMATRIX worldMatrix)
{
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixTranspose(XMMatrixInverse(nullptr, worldMatrix));
	//cb.matWorld = XMMatrixTranspose(worldMatrix);

	D3D11_MAPPED_SUBRESOURCE pdata;
	HRESULT hr = Direct3D::pContext->Map(constantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);

    // ワールド×ビュー×プロジェクション行列の合成と転置
    XMMATRIX view = Camera::GetViewMatrix();
    XMMATRIX proj = Camera::GetProjectionMatrix();
    XMMATRIX wvp = worldMatrix * view * proj;
    wvp = XMMatrixTranspose(wvp);

    // 定数バッファへ転送
    Direct3D::pContext->UpdateSubresource(constantBuffer_, 0, nullptr, &wvp, 0, 0);

    // 頂点バッファセット
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    Direct3D::pContext->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
    Direct3D::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // テクスチャセット
    ID3D11ShaderResourceView* srv = texture_->GetSRV();
    Direct3D::pContext->PSSetShaderResources(0, 1, &srv);

    ID3D11SamplerState* sampler = texture_->GetSampler();
    Direct3D::pContext->PSSetSamplers(0, 1, &sampler);

    // 定数バッファセット（VSスロット0）
    Direct3D::pContext->VSSetConstantBuffers(0, 1, &constantBuffer_);

    // 描画
    Direct3D::pContext->Draw(36, 0);
}
