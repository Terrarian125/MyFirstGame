#pragma once
#include "Engine\\GameObject.h"

class Fbx;
//class ChildOden;

class Bar :
	public GameObject
{
public:
	Bar(GameObject* parent);
	~Bar();
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