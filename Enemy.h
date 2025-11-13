#pragma once
#include "Engine\\GameObject.h"

class Fbx;
//class ChildOden;

class Enemy :
	public GameObject
{
public:
	Enemy(GameObject* parent);
	~Enemy();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	Fbx* pFbx_;
	int hModel_;
	//onCollision
	void onCollision(GameObject* pTarget) override;

	//ChildOden* pRChildOden_;
	//ChildOden* pLChildOden_;
};