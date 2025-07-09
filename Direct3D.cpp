#include <d3dcompiler.h>
#include "Direct3D.h"
#include <assert.h>
#include <d3d11.h>
#include <DirectXMath.h>

HWND g_hWnd = nullptr;

using namespace DirectX;

namespace Direct3D {
    ID3D11Device* pDevice = nullptr;
    ID3D11DeviceContext* pContext = nullptr;
    IDXGISwapChain* pSwapChain = nullptr;
    ID3D11RenderTargetView* pRenderTargetView = nullptr;

    ID3D11VertexShader* pVertexShader = nullptr;
    ID3D11PixelShader* pPixelShader = nullptr;

    ID3D11InputLayout* pVertexLayout = nullptr;
    ID3D11RasterizerState* pRasterizerState = nullptr;
}

// ������
HRESULT Direct3D::Initialize(int winW, int winH, HWND hWnd)
{
    g_hWnd = hWnd;
    DXGI_SWAP_CHAIN_DESC scDesc = {};
    scDesc.BufferDesc.Width = winW;
    scDesc.BufferDesc.Height = winH;
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferDesc.RefreshRate.Numerator = 60;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;
    scDesc.Windowed = TRUE;
    scDesc.OutputWindow = hWnd;
    scDesc.BufferCount = 1;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;

    D3D_FEATURE_LEVEL level;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &scDesc,
        &Direct3D::pSwapChain,
        &Direct3D::pDevice,
        &level,
        &Direct3D::pContext);

    if (FAILED(hr)) {
        MessageBox(nullptr, L"Direct3D�f�o�C�X�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
        return hr;
    }

    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = Direct3D::pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr)) {
        MessageBox(nullptr, L"�o�b�N�o�b�t�@�̎擾�Ɏ��s���܂���", L"�G���[", MB_OK);
        return hr;
    }

    hr = Direct3D::pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &Direct3D::pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr)) {
        MessageBox(nullptr, L"�����_�[�^�[�Q�b�g�r���[�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
        return hr;
    }

    D3D11_VIEWPORT vp = {};
    vp.Width = static_cast<float>(winW);
    vp.Height = static_cast<float>(winH);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    Direct3D::pContext->RSSetViewports(1, &vp);
    Direct3D::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    Direct3D::pContext->OMSetRenderTargets(1, &Direct3D::pRenderTargetView, nullptr);

    hr = InitShader();
    if (FAILED(hr)) {
        MessageBox(nullptr, L"�V�F�[�_�[�������Ɏ��s���܂���", L"�G���[", MB_OK);
        return hr;
    }

    return S_OK;
}

// �V�F�[�_�[�̏�����
HRESULT Direct3D::InitShader()
{
    HRESULT hr;

    // ���_�V�F�[�_�̍쐬�i�R���p�C���j
    ID3DBlob* pCompileVS = nullptr;
    hr = D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &pCompileVS, nullptr);
    if (FAILED(hr) || pCompileVS == nullptr) {
        MessageBox(nullptr, L"���_�V�F�[�_�̃R���p�C���Ɏ��s���܂���", L"�G���[", MB_OK);
        return hr;
    }

    hr = Direct3D::pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), nullptr, &Direct3D::pVertexShader);
    if (FAILED(hr)) {
        pCompileVS->Release();
        MessageBox(nullptr, L"���_�V�F�[�_�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
        return hr;
    }

    // ���̓��C�A�E�g�ݒ�
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,   D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    hr = Direct3D::pDevice->CreateInputLayout(layout, _countof(layout), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &Direct3D::pVertexLayout);
    pCompileVS->Release();
    if (FAILED(hr)) {
        MessageBox(nullptr, L"���̓��C�A�E�g�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
        return hr;
    }

    // �s�N�Z���V�F�[�_�[�̃R���p�C��
    ID3DBlob* pCompilePS = nullptr;
    hr = D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &pCompilePS, nullptr);
    if (FAILED(hr) || pCompilePS == nullptr) {
        MessageBox(nullptr, L"�s�N�Z���V�F�[�_�̃R���p�C���Ɏ��s���܂���", L"�G���[", MB_OK);
        return hr;
    }

    hr = Direct3D::pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), nullptr, &Direct3D::pPixelShader);
    pCompilePS->Release();
    if (FAILED(hr)) {
        MessageBox(nullptr, L"�s�N�Z���V�F�[�_�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
        return hr;
    }

    // ���X�^���C�U�쐬
    D3D11_RASTERIZER_DESC rdc = {};
    rdc.CullMode = D3D11_CULL_BACK;
    rdc.FillMode = D3D11_FILL_SOLID;
    rdc.FrontCounterClockwise = FALSE;
    hr = Direct3D::pDevice->CreateRasterizerState(&rdc, &Direct3D::pRasterizerState);
    if (FAILED(hr)) {
        MessageBox(nullptr, L"���X�^���C�U�X�e�[�g�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
        return hr;
    }

    // �f�o�C�X�R���e�L�X�g�ɃV�F�[�_�[�Ɛݒ���Z�b�g
    Direct3D::pContext->VSSetShader(Direct3D::pVertexShader, nullptr, 0);
    Direct3D::pContext->PSSetShader(Direct3D::pPixelShader, nullptr, 0);
    Direct3D::pContext->IASetInputLayout(Direct3D::pVertexLayout);
    Direct3D::pContext->RSSetState(Direct3D::pRasterizerState);

    return S_OK;
}


// �`��J�n
void Direct3D::BeginDraw()
{
    float clearColor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };
    Direct3D::pContext->ClearRenderTargetView(Direct3D::pRenderTargetView, clearColor);
}

// �`��I��
void Direct3D::EndDraw()
{
    Direct3D::pSwapChain->Present(0, 0);
}

// ���
void Direct3D::Release()
{
    if (Direct3D::pRasterizerState) { Direct3D::pRasterizerState->Release(); Direct3D::pRasterizerState = nullptr; }
    if (Direct3D::pVertexLayout) { Direct3D::pVertexLayout->Release(); Direct3D::pVertexLayout = nullptr; }
    if (Direct3D::pPixelShader) { Direct3D::pPixelShader->Release(); Direct3D::pPixelShader = nullptr; }
    if (Direct3D::pVertexShader) { Direct3D::pVertexShader->Release(); Direct3D::pVertexShader = nullptr; }
    if (Direct3D::pRenderTargetView) { Direct3D::pRenderTargetView->Release(); Direct3D::pRenderTargetView = nullptr; }
    if (Direct3D::pSwapChain) { Direct3D::pSwapChain->Release(); Direct3D::pSwapChain = nullptr; }
    if (Direct3D::pContext) { Direct3D::pContext->Release(); Direct3D::pContext = nullptr; }
    if (Direct3D::pDevice) { Direct3D::pDevice->Release(); Direct3D::pDevice = nullptr; }
}
