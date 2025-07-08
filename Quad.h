#pragma once  
#include <DirectXMath.h>
#include "Direct3D.h"  
#include "Texture.h"

using namespace DirectX;

// コンスタントバッファー  
struct CONSTANT_BUFFER  
{  
   DirectX::XMMATRIX matWVP; 
};  

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};

class Texture; // 前方宣言

class Quad  
{  
public:  
   Quad();  
   ~Quad();  
  HRESULT Initialize();  
   void Draw(DirectX::XMMATRIX& worldMatrix);
   void Release();  
private:
	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer* pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	Texture* pTexture_;
};