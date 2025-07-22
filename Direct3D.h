#pragma once
#include <d3d11.h>
#include<windows.h>
//隣家
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p){ (p)->Release(); (p) = nullptr; }

enum SHADER_TYPE
{
	SHADER_3D,  //3D用シェーダ
	SHADER_2D,  //2D用シェーダ	
	SHADER_MAX //シェーダの最大数
};

namespace Direct3D
{
	extern ID3D11DeviceContext* pContext;
	extern ID3D11Device* pDevice;

	static HWND g_hWnd;
	//HWND g_hWnd = nullptr;
	const int winW = 800;
	const int winH = 600;

	//シェーダー準備
	HRESULT InitShader();
	HRESULT InitShader3D();
	HRESULT InitShader2D();

	void SetShader(SHADER_TYPE type); 

	//初期化
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//描画開始
	void BeginDraw();

	//描画終了
	void EndDraw();

	//解放
	void Release();
};