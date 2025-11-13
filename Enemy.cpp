#include "Enemy.h"
#include "Engine/Fbx.h"
//#include "ChildOden.h"
#include "Engine\\Model.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), pFbx_(nullptr), hModel_(-1)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{

	pFbx_ = new Fbx();
	//pFbx_->Load("pumpkin.fbx");

	transform_.scale_ = { 0.35f,0.4f,0.35f };
	transform_.position_.z = 4.0f;

	hModel_ = Model::Load("pumpkin.fbx");
	//hModel_ = Model::Load("Bulet.fbx");

	assert(hModel_ >= 0);

}

void Enemy::Update()
{
	transform_.rotate_.y += 0.7f;
	
	//ã‰ºˆÚ“®
	static float y = 2.0;
	float ty = sin(y) * 2.0f;
	y += 0.02f;
	transform_.position_.y = ty;
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
	if (pFbx_) {
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}


