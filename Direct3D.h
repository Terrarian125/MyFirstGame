#pragma once
#include <d3d11.h>
#include<windows.h>
//�׉�
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
// Direct3D.h
#pragma once

namespace Direct3D {
    extern ID3D11Device* pDevice;
    extern ID3D11DeviceContext* pContext;
    // ...���̐錾
}
namespace Direct3D
{
	extern ID3D11Device* pDevice;

	HWND g_hWnd = nullptr;
	const int winW = 800;
	const int winH = 600;
	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader();

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();
};