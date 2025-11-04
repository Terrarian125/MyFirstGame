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
	//Fbx‚Ì¶¬‚Æ‰Šú‰»

	pFbx_ = new Fbx();
	pFbx_->Load("pumpkin.fbx");
	transform_.scale_.x = 0.4f;
	transform_.scale_.y = 0.4f;
	transform_.scale_.z = 0.4f;
	transform_.position_.x = 2.0f;
	transform_.position_.y = 1.3f;

	hModel_ = Model::Load("pumpkin.fbx");

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
