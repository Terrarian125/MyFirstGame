#include "Player.h"
#include "Engine/Fbx.h"
#include "ChildOden.h"
#include "Engine\\Model.h"
#include "Engine/SphereCollider.h"
#include "Engine\\Input.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx_(nullptr), hModel_(-1)
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
	hModel_ = Model::Load("Oden.fbx");
	assert(hModel_ >= 0);

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void Player::Update()
{
	static float x = 0.0;
	float tx = sin(x) * 5.0f;
	x += 0.02f;
	
	//transform_rotate_.y += 2.0f;
	if (Input::IsKey(DIK_SPACE)) {
		transform_.position_.z += 0.5f;
	}
}

void Player::Draw()
{
	//if (pFbx_) {
	//	pFbx_->Draw(transform_);
	//}
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
	if (pFbx_) {
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}

//なんんかにあたった
void Player::OnCollision(GameObject** pTsrget)
{
	int a = 0;
}
