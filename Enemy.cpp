#include "Enemy.h"
#include "Engine/Fbx.h"
#include "Engine\\Model.h"
#include "Engine/SphereCollider.h"
#include "Bullet.h"
#include "Engine/SceneManager.h"

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

	transform_.scale_ = { 0.35f,0.4f,0.35f };
	transform_.position_.z = 4.0f;

	hModel_ = Model::Load("pumpkin.fbx");

	SphereCollider* collision = new SphereCollider(0.5f);
	AddCollider(collision);
}

void Enemy::Update()
{
	transform_.rotate_.y += 0.7f;
	
	//上下移動
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

void Enemy::onCollision(GameObject* pTarget)
{
	// 衝突相手が Bullet クラスであるかを確認
	Bullet* pBullet = dynamic_cast<Bullet*>(pTarget);

	if (pBullet != nullptr)
	{
		// pTarget は Bullet である

		// 敵（自分自身）を削除する
		this->KillMe();

		// テストシーンに移動
		GameObject* sceneManager = GetRootJob()->FindChildObject("SceneManager");
		if (sceneManager != nullptr)
		{
			static_cast<SceneManager*>(sceneManager)->ChangeScene(SCENE_ID_CLEARE);
		}
		
	}
	// 衝突相手が Bullet 以外の場合は何もしない
}