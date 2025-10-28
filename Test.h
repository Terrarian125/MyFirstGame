#pragma once
#include "Engine\\GameObject.h"

class Fbx;
//class ChildOden;

class Test :
	public GameObject
{
public:
	Test(GameObject* parent);
	~Test();
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

