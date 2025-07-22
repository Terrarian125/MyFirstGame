//Quad.h
#pragma once  
#include <DirectXMath.h>
#include "Direct3D.h"  
#include "Texture.h"

using namespace DirectX;

// �R���X�^���g�o�b�t�@�[  
struct CONSTANT_BUFFER  
{  
   DirectX::XMMATRIX matWVP; 
   DirectX::XMMATRIX	matW;
};  

//���_���
struct VERTEX
{
	XMFLOAT4 position;
	XMFLOAT2 uv;
	XMFLOAT3 normal;
};

class Texture; // �O���錾

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