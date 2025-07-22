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

    // �e�N�X�`���̃��[�h
    texture_ = new Texture();
    hr = texture_->Load("Assets/Dice.png");
    if (FAILED(hr)) return hr;

    // ���_�o�b�t�@�̍쐬
    hr = CreateVertexBuffer();
    if (FAILED(hr)) return hr;

    // �萔�o�b�t�@�̍쐬
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
    Vertex vertices[36]; // 6�� �~ 2�O�p�` �~ 3���_ = 36���_

    const float texWidth = 512.0f;
    const float texHeight = 256.0f;
    const float faceWidthUV = 128.0f / texWidth;  // 0.25
    const float faceHeightUV = 128.0f / texHeight; // 0.5

    struct UVOffset { float u; float v; };
    UVOffset uvOffsets[6] = {
        { 0.0f * faceWidthUV, 0.0f * faceHeightUV }, // ��1 (��i���[)
        { 1.0f * faceWidthUV, 0.0f * faceHeightUV }, // ��2
        { 2.0f * faceWidthUV, 0.0f * faceHeightUV }, // ��3
        { 3.0f * faceWidthUV, 0.0f * faceHeightUV }, // ��4
        { 0.0f * faceWidthUV, 1.0f * faceHeightUV }, // ��5 (���i���[)
        { 1.0f * faceWidthUV, 1.0f * faceHeightUV }  // ��6
    };

    auto SetFaceVertices = [&](int faceIndex, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, XMFLOAT3 v3)
        {
            int base = faceIndex * 6;
            float uOff = uvOffsets[faceIndex].u;
            float vOff = uvOffsets[faceIndex].v;

            // ����A�E��A�����A�E��A�E���A���� �̏��ŎO�p�`2���
            vertices[base + 0] = { v0, XMFLOAT2(uOff, vOff) };
            vertices[base + 1] = { v1, XMFLOAT2(uOff + faceWidthUV, vOff) };
            vertices[base + 2] = { v2, XMFLOAT2(uOff, vOff + faceHeightUV) };
            vertices[base + 3] = { v1, XMFLOAT2(uOff + faceWidthUV, vOff) };
            vertices[base + 4] = { v3, XMFLOAT2(uOff + faceWidthUV, vOff + faceHeightUV) };
            vertices[base + 5] = { v2, XMFLOAT2(uOff, vOff + faceHeightUV) };
        };

    // 6�ʂ̒��_���W
    SetFaceVertices(0, // �O�� (Z+)
        XMFLOAT3(-0.5f, 0.5f, 0.5f),
        XMFLOAT3(0.5f, 0.5f, 0.5f),
        XMFLOAT3(-0.5f, -0.5f, 0.5f),
        XMFLOAT3(0.5f, -0.5f, 0.5f));

    SetFaceVertices(1, // �w�� (Z-)
        XMFLOAT3(0.5f, 0.5f, -0.5f),
        XMFLOAT3(-0.5f, 0.5f, -0.5f),
        XMFLOAT3(0.5f, -0.5f, -0.5f),
        XMFLOAT3(-0.5f, -0.5f, -0.5f));

    SetFaceVertices(2, // ��� (Y+)
        XMFLOAT3(-0.5f, 0.5f, -0.5f),
        XMFLOAT3(0.5f, 0.5f, -0.5f),
        XMFLOAT3(-0.5f, 0.5f, 0.5f),
        XMFLOAT3(0.5f, 0.5f, 0.5f));

    SetFaceVertices(3, // ��� (Y-)
        XMFLOAT3(-0.5f, -0.5f, 0.5f),
        XMFLOAT3(0.5f, -0.5f, 0.5f),
        XMFLOAT3(-0.5f, -0.5f, -0.5f),
        XMFLOAT3(0.5f, -0.5f, -0.5f));

    SetFaceVertices(4, // �E�� (X+)
        XMFLOAT3(0.5f, 0.5f, 0.5f),
        XMFLOAT3(0.5f, 0.5f, -0.5f),
        XMFLOAT3(0.5f, -0.5f, 0.5f),
        XMFLOAT3(0.5f, -0.5f, -0.5f));

    SetFaceVertices(5, // ���� (X-)
        XMFLOAT3(-0.5f, 0.5f, -0.5f),
        XMFLOAT3(-0.5f, 0.5f, 0.5f),
        XMFLOAT3(-0.5f, -0.5f, -0.5f),
        XMFLOAT3(-0.5f, -0.5f, 0.5f));

    // �o�b�t�@�쐬
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

    // ���[���h�~�r���[�~�v���W�F�N�V�����s��̍����Ɠ]�u
    XMMATRIX view = Camera::GetViewMatrix();
    XMMATRIX proj = Camera::GetProjectionMatrix();
    XMMATRIX wvp = worldMatrix * view * proj;
    wvp = XMMatrixTranspose(wvp);

    // �萔�o�b�t�@�֓]��
    Direct3D::pContext->UpdateSubresource(constantBuffer_, 0, nullptr, &wvp, 0, 0);

    // ���_�o�b�t�@�Z�b�g
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    Direct3D::pContext->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
    Direct3D::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // �e�N�X�`���Z�b�g
    ID3D11ShaderResourceView* srv = texture_->GetSRV();
    Direct3D::pContext->PSSetShaderResources(0, 1, &srv);

    ID3D11SamplerState* sampler = texture_->GetSampler();
    Direct3D::pContext->PSSetSamplers(0, 1, &sampler);

    // �萔�o�b�t�@�Z�b�g�iVS�X���b�g0�j
    Direct3D::pContext->VSSetConstantBuffers(0, 1, &constantBuffer_);

    // �`��
    Direct3D::pContext->Draw(36, 0);
}
