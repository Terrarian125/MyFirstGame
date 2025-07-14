#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Texture.h"

class Dice
{
public:
    Dice();
    ~Dice();

    HRESULT Initialize();
    void Draw(DirectX::XMMATRIX worldMatrix);

private:
    HRESULT CreateVertexBuffer();

    ID3D11Buffer* vertexBuffer_;
    ID3D11Buffer* constantBuffer_;
    Texture* texture_;

    struct Vertex
    {
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT2 uv;
    };
};
