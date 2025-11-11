#include "Bullet.h"

//#include "ChildOden.h"
#include "Engine\\Model.h"

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), pFbx_(nullptr), hModel_(-1)
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{

	pFbx_ = new Fbx();
	//pFbx_->Load("pumpkin.fbx");

	transform_.scale_ = { 1.0f,1.0f,1.0f };
	transform_.position_.z = 50.0f;

	//hModel_ = Model::Load("pumpkin.fbx");
	hModel_ = Model::Load("Bulet.fbx");

	assert(hModel_ >= 0);

}

void Bullet::Update()
{
	transform_.rotate_.y += 0.4f;
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}


