#include "GameObject.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const string& name)
	: pParent_(parent), objectName_(name)
{
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
}
