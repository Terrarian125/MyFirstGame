#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

struct CONSTANT_BUFFER
{
	DirectX::XMMATRIX matWorld; //ワールド行列
};

struct VERTEX
{
	XMFLOAT4 pos;	//位置
	XMFLOAT2 uv;	//UV座標
};

//前方宣言
class Texture;//Textureクラスってのがどこかにあってだなぁ宣言

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();
	virtual HRESULT Initialize();
	virtual void Draw(XMMATRIX& worldMatrix);
	void Release();
protected:
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;	//インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//定数バッファ
	Texture* pTexture_;	//テクスチャ
};

