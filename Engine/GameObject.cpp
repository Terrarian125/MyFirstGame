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
//�����Ǝq�I�u�W�F�N�g��`��
	Draw();
	for (auto child : childList_) {
		child->DrawSub();
	}
}
