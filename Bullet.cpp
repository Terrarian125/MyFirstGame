#include "Bullet.h"
#include "Engine\\Model.h"
#include "Engine\\Model.h"
//#include "Engine/SphereCollider.h"

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), pFbx_(nullptr), hModel_(-1), life_(600)
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

	hModel_ = Model::Load("Bulet.fbx");

	//SphereCollider* collision = new SphereCollider(0.32f);
	//AddCollider(collision);

}

void Bullet::Update()
{
	transform_.scale_ = { 0.3f,0.3f,0.3f };
	transform_.position_.z += 0.4f;
	transform_.rotate_.y += 0.2f;
	life_--;
	if (life_ <= 0)
	{
		KillMe();
	}
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}

void Bullet::onCollision(GameObject* pTarget)
{
	// Ž©•ªŽ©g‚ðíœ‚·‚é
	this->KillMe();
}
