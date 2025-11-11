#pragma once
#include "Engine/GameObject.h"

class Fbx;

class ChildOden :
	public GameObject
{
public:
	ChildOden(GameObject* parent);
	~ChildOden();
	//純粋仮想関数のオーバーライド
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
private:
	Fbx* pFbx_;
	int hModel_;//モデルハンドル
};