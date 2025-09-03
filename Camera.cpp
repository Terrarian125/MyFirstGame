#include "Camera.h"

//変数
XMVECTOR position_;	//カメラの位置（視点）
XMVECTOR target_;	//見る位置（焦点）
XMMATRIX viewMatrix_;	//ビュー行列
XMMATRIX projMatrix_;	//プロジェクション行列

//初期化
void Camera::Initialize()
{
	position_ = XMVectorSet(0, 3, -10, 0);	//カメラの位置
	target_ = XMVectorSet(0, 0, 0, 0);	//カメラの焦点

	//プロジェクション行列
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);
}

//更新
void Camera::Update()
{
	//ビュー行列の作成
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));

	// 上下左右の移動
	XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMVectorSubtract(target_, position_), XMVectorSet(0, 1, 0, 0)));
	XMVECTOR forward = XMVector3Normalize(XMVector3Cross(XMVectorSet(0, 1, 0, 0), right));
	XMVECTOR up = XMVectorSet(0, 1, 0, 0); // 上方向

	const float moveSpeed = 0.003f;
	const float rotateSpeed = 0.001f;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		XMVECTOR move = XMVectorScale(forward, moveSpeed);
		position_ = XMVectorAdd(position_, move);
		target_ = XMVectorAdd(target_, move);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		XMVECTOR move = XMVectorScale(forward, -moveSpeed);
		position_ = XMVectorAdd(position_, move);
		target_ = XMVectorAdd(target_, move);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		XMVECTOR move = XMVectorScale(right, moveSpeed);
		position_ = XMVectorAdd(position_, move);
		target_ = XMVectorAdd(target_, move);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		XMVECTOR move = XMVectorScale(right, -moveSpeed);
		position_ = XMVectorAdd(position_, move);
		target_ = XMVectorAdd(target_, move);
	}
	// 高さ調整（上昇）
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		XMVECTOR move = XMVectorScale(up, moveSpeed);
		position_ = XMVectorAdd(position_, move);
		target_ = XMVectorAdd(target_, move);
	}
	// 高さ調整（下降）
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		XMVECTOR move = XMVectorScale(up, -moveSpeed);
		position_ = XMVectorAdd(position_, move);
		target_ = XMVectorAdd(target_, move);
	}
	// ←→キーで左右に回転（Yaw）
	XMVECTOR direction = XMVectorSubtract(target_, position_);
	XMMATRIX rotMatrix;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		rotMatrix = XMMatrixRotationY(-rotateSpeed);
		direction = XMVector3TransformNormal(direction, rotMatrix);
		target_ = XMVectorAdd(position_, direction);
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		rotMatrix = XMMatrixRotationY(rotateSpeed);
		direction = XMVector3TransformNormal(direction, rotMatrix);
		target_ = XMVectorAdd(position_, direction);
	}
}

//位置を設定
void Camera::SetPosition(XMVECTOR position)
{
	position_ = position;	//カメラの位置を設定
}

//焦点を設定
void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;	//見る位置（焦点）を設定
}

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix_;	//ビュー行列を返す
}

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;	//プロジェクション行列を返す
}