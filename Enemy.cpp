#include "Enemy.h"
#include "Engine/Fbx.h"
//#include "ChildOden.h"
#include "Engine\\Model.h"
#include "Engine/SphereCollider.h"


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
	transform_.position_ = { 0.0f,0.0f,50.0f };

	hModel_ = Model::Load("pumpkin.fbx");

	assert(hModel_ >= 0);

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Enemy::Update()
{
	transform_.rotate_.y += 11.4f;
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
