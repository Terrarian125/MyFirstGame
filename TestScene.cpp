#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"


TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
}

void TestScene::Update()
{
	//スペースキーが押されたらPlaySceneに切り替え（SceneManager::ChangeScene(SCENE_ID_PLAY);を呼び出す）
	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject* sceneManager = GetRootJob()->FindChildObject("SceneManager");
		if (sceneManager != nullptr)
		{
			static_cast<SceneManager*>(sceneManager)->ChangeScene(SCENE_ID_PLAY);
		}
	}

}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
