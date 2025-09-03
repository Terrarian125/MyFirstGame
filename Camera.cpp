#include "Camera.h"

//�ϐ�
XMVECTOR position_;	//�J�����̈ʒu�i���_�j
XMVECTOR target_;	//����ʒu�i�œ_�j
XMMATRIX viewMatrix_;	//�r���[�s��
XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��

//������
void Camera::Initialize()
{
	position_ = XMVectorSet(0, 3, -10, 0);	//�J�����̈ʒu
	target_ = XMVectorSet(0, 0, 0, 0);	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);
}

//�X�V
void Camera::Update()
{
	//�r���[�s��̍쐬
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));

	// �㉺���E�̈ړ�
	XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMVectorSubtract(target_, position_), XMVectorSet(0, 1, 0, 0)));
	XMVECTOR forward = XMVector3Normalize(XMVector3Cross(XMVectorSet(0, 1, 0, 0), right));
	XMVECTOR up = XMVectorSet(0, 1, 0, 0); // �����

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
	// ���������i�㏸�j
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		XMVECTOR move = XMVectorScale(up, moveSpeed);
		position_ = XMVectorAdd(position_, move);
		target_ = XMVectorAdd(target_, move);
	}
	// ���������i���~�j
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		XMVECTOR move = XMVectorScale(up, -moveSpeed);
		position_ = XMVectorAdd(position_, move);
		target_ = XMVectorAdd(target_, move);
	}
	// �����L�[�ō��E�ɉ�]�iYaw�j
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

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position)
{
	position_ = position;	//�J�����̈ʒu��ݒ�
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target)
{
	target_ = target;	//����ʒu�i�œ_�j��ݒ�
}

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix_;	//�r���[�s���Ԃ�
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;	//�v���W�F�N�V�����s���Ԃ�
}