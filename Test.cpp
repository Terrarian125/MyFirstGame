#include "Test.h"
#include "Engine/Fbx.h"
//#include "ChildOden.h"
#include "Engine\\Model.h"

Test::Test(GameObject* parent)
	:GameObject(parent, "Test"), pFbx_(nullptr), hModel_(-1)
{
}

Test::~Test()
{
}

void Test::Initialize()
{
	//Fbx‚Ì¶¬‚Æ‰Šú‰»

	pFbx_ = new Fbx();
	pFbx_->Load("Test.fbx");
	transform_.scale_.x = 0.7f;
	transform_.scale_.y = 0.7f;
	transform_.scale_.z = 0.7f;

	hModel_ = Model::Load("Test.fbx");

	assert(hModel_ >= 0);

}

void Test::Update()
{
}

void Test::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Test::Release()
{
	if (pFbx_) {
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}
