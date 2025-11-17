#include "ClearScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "CL_obg.h"

ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene")
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	// モデルを生成して、子に追加  
	Instanitiate<CL_obg>(this);

}

void ClearScene::Update()
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

void ClearScene::Draw()
{
}

void ClearScene::Release()
{
}
