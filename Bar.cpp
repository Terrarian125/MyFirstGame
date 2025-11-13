#include "Bar.h"
#include "Engine/Fbx.h"
//#include "ChildOden.h"
#include "Engine\\Model.h"

Bar::Bar(GameObject* parent)
	:GameObject(parent, "Bar"), pFbx_(nullptr), hModel_(-1)
{
}

Bar::~Bar()
{
}

void Bar::Initialize()
{

	pFbx_ = new Fbx();

	transform_.scale_ = {5.0f,5.0f,5.0f };
	transform_.position_.y = -2.0f;
	transform_.position_.x = 3.0f;

	hModel_ = Model::Load("St.fbx");
	//hModel_ = Model::Load("Bulet.fbx");

	assert(hModel_ >= 0);

}

void Bar::Update()
{
}

void Bar::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	//‰æ‘œ‚ð•\Ž¦

}

void Bar::Release()
{
	if (pFbx_) {
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}


