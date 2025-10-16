#include "Player.h"
#include "Engine/Fbx.h"
#include "ChildOden.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx_(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//Fbxの生成と初期化
	pFbx_ = new Fbx();
	pFbx_->Load("Oden.fbx");
	transform_.scale_.x = 0.7f;
	transform_.scale_.y = 0.7f;
	transform_.scale_.z = 0.7f;
	//子オブジェクトにChildOdenを追加
	pRChildOden_ = (ChildOden *)Instanitiate<ChildOden>(this);
	pLChildOden_ = (ChildOden *)Instanitiate<ChildOden>(this);
	pRChildOden_->SetPosition(2.0f, 1.3f, 0.0f);
	pLChildOden_->SetPosition(-2.0f, 1.3f, 0.0f);
}

void Player::Update()
{
	//おでんを回転させる
	transform_.rotate_.y += 2.0f;
	if (transform_.rotate_.y > 720.0f) 
	{
		KillMe();
	}
}

void Player::Draw()
{
	if (pFbx_) {
		pFbx_->Draw(transform_);
	}
}

void Player::Release()
{
	if (pFbx_) {
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}
