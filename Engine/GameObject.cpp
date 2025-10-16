#include "GameObject.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const string& name)
	: pParent_(parent), objectName_(name), isDead_(false)
{
	if (parent != nullptr)
	{
		transform_.pParent_ = &(parent->transform_);
	}
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
//自分と子オブジェクトを描画
	Draw();
	for (auto child : childList_) {
		child->DrawSub();
	}
	for (auto itr = childList_.begin(); itr != childList_.end(); ) 
	{
		if ((*itr)->isDead_) 
		{
			(*itr)->ReleaseSub();
			delete (*itr);
			itr = childList_.erase(itr);
		}
		else 
		{
			++itr;
		}
	}
}

void GameObject::UpdateSub()
{
	Update();
	for (auto child : childList_) {
		child->UpdateSub();
	}
}

void GameObject::ReleaseSub()
{
	this->Release();//自分を解放
	for (auto child : childList_) {
		child->ReleaseSub();
	}
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	transform_.position_ = { x, y, z };
}

void GameObject::KillMe()
{
	isDead_ = true;
}