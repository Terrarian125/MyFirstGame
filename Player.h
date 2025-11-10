#pragma once
#include "Engine\\GameObject.h"
//#include "Engine\\Model.h"

class Fbx;
class ChildOden;

class Player :
    public GameObject
{
public:
	Player(GameObject* parent);
	~Player();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void OnCollision(GameObject** pTsrget)override;
private:
	Fbx* pFbx_;
	int hModel_;
	ChildOden* pRChildOden_;
	ChildOden* pLChildOden_;
};

