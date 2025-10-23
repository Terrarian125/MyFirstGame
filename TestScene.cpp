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
	//�X�y�[�X�L�[�������ꂽ��PlayScene�ɐ؂�ւ��iSceneManager::ChangeScene(SCENE_ID_PLAY);���Ăяo���j
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
