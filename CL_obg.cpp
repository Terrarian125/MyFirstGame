#include "CL_obg.h"
#include "Engine/Fbx.h"
#include "Engine\\Model.h"
#include "Engine/SphereCollider.h"
//#include "Bullet.h"
//#include "Engine/SceneManager.h"

CL_obg::CL_obg(GameObject* parent)
	:GameObject(parent, "CL_obg"), pFbx_(nullptr), hModel_(-1)
{
}

CL_obg::~CL_obg()
{
}

void CL_obg::Initialize()
{

	pFbx_ = new Fbx();

	transform_.scale_ = { 0.5f,0.5f,0.5f };
	transform_.position_.z = 0.0f;

	hModel_ = Model::Load("CL_obg.fbx");

	SphereCollider* collision = new SphereCollider(0.5f);
	AddCollider(collision);
}

void CL_obg::Update()
{
	transform_.rotate_.y += 0.3f;

	//ã‰ºˆÚ“®
	static float y = 1.0;
	float ty = sin(y) * 1.0f;
	y += 0.02f;
	transform_.position_.y = ty;
}

void CL_obg::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void CL_obg::Release()
{
	if (pFbx_) {
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}

void CL_obg::onCollision(GameObject* pTarget)
{
}