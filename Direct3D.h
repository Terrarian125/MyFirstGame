#pragma once
#include <d3d11.h>
#include<windows.h>
//隣家
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
// Direct3D.h
#pragma once

namespace Direct3D {
    extern ID3D11Device* pDevice;
    extern ID3D11DeviceContext* pContext;
    // ...他の宣言
}
namespace Direct3D
{
	extern ID3D11Device* pDevice;

	HWND g_hWnd = nullptr;
	const int winW = 800;
	const int winH = 600;
	//初期化
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//シェーダー準備
	HRESULT InitShader();

	//描画開始
	void BeginDraw();

	//描画終了
	void EndDraw();

	//解放
	void Release();
};