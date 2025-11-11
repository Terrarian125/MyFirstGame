#pragma once
#include "Engine\\GameObject.h"
#include "Engine/Fbx.h"
class Fbx;
//class ChildOden;

class Bullet :
	public GameObject
{
public:
	Bullet(GameObject* parent);
	~Bullet();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	Fbx* pFbx_;
	int hModel_;
	//ChildOden* pRChildOden_;
	//ChildOden* pLChildOden_;
};