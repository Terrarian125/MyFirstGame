#include "Transform.h"
//QuadクラスのDraw関数にTransformオブジェクトを渡すことで変形できるように改良する!
Transform::Transform()
{
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);
	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
}

Transform::~Transform()
{
}

void Transform::Calculation()
{
	//移動行列
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);
	matRotate_ = XMMatrixRotationRollPitchYaw(
		XMConvertToRadians(rotate_.x),
		XMConvertToRadians(rotate_.y),
		XMConvertToRadians(rotate_.z));
	//拡大縮小
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
	return matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::GetNormalMatrix()
{
	return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}
