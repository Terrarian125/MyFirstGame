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

	transform_.scale_ = { 1.0f,1.0f,1.0f };
	transform_.position_.z = 50.0f;

	hModel_ = Model::Load("pumpkin.fbx");
	//hModel_ = Model::Load("Bulet.fbx");

	assert(hModel_ >= 0);

}

void Enemy::Update()
{
	transform_.rotate_.y += 0.4f;
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


