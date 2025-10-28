#pragma once
#include "Engine\\GameObject.h"
//#include "Engine/SceneManager.h"

class TestScene :
    public GameObject
{
public:
	TestScene(GameObject* parent);
	~TestScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};

