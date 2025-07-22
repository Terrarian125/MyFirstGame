#pragma once
#include <d3d11.h>
#include<windows.h>
//�׉�
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p){ (p)->Release(); (p) = nullptr; }

enum SHADER_TYPE
{
	SHADER_3D,  //3D�p�V�F�[�_
	SHADER_2D,  //2D�p�V�F�[�_	
	SHADER_MAX //�V�F�[�_�̍ő吔
};

namespace Direct3D
{
	extern ID3D11DeviceContext* pContext;
	extern ID3D11Device* pDevice;

	static HWND g_hWnd;
	//HWND g_hWnd = nullptr;
	const int winW = 800;
	const int winH = 600;

	//�V�F�[�_�[����
	HRESULT InitShader();
	HRESULT InitShader3D();
	HRESULT InitShader2D();

	void SetShader(SHADER_TYPE type); 

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();
};