#include "Camera.h"

//�ϐ�
XMVECTOR position_;	//�J�����̈ʒu�i���_�j
XMVECTOR target_;	//����ʒu�i�œ_�j
XMMATRIX viewMatrix_;	//�r���[�s��
XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��

//������
void Camera::Initialize()
{
	position_ = XMVectorSet(0.0f, 3.0f, -10.0f, 1.0f); // �J�����̏����ʒu
	target_ = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f); // �J�����̏œ_

	//�v���W�F�N�V�����s��
	projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);
}

//�X�V
void Camera::Update()
{
	viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
}

//�ʒu��ݒ�
void Camera::SetPosition(XMVECTOR position)
{
}

//�œ_��ݒ�
void Camera::SetTarget(XMVECTOR target)
{
}

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix_;
}

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	return projMatrix_;
}