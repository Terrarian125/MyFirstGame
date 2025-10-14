#pragma once

#include <list>
#include <string>
#include "Transform.h"

using std::string;
using std::list;

class GameObject
{
public:
	GameObject();
	GameObject(GameObject* parent, const string& name);
	virtual ~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
	void DrawSub();
	template <typename T>
	void Instanitiate(GameObject* parent) {
		T* obj = new T(parent);
		obj->Initialize();
		childList_.push_back(obj);
	}
protected:
	list<GameObject*> childList_;
	Transform transform_;
	GameObject* pParent_;
	string objectName_;
};