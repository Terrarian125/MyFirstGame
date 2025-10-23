#include "Direct3D.h"
#include "SceneManager.h"
#include "..\\PlayScene.h"
//#include "..\Model.h"
//#include 

SceneManager::SceneManager(GameObject* parent)
	: GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instanitiate<PlayScene>(this);
}

void SceneManager::Update()
{
	if (currentSceneID_ != nextSceneID_)
	{
		// ƒV[ƒ“Ø‚è‘Ö‚¦ˆ—
		auto scene = childList_.front();
		scene->ReleaseSub();
		SAFE_DELETE(scene);
		childList_.clear();
			
		switch (nextSceneID_)
		{
		case SCENE_ID_PLAY:
			Instanitiate<PlayScene>(this);
			break;
		case SCENE_ID_TEST:
			//Instanitiate<TestScene>(this);
			break;
		}
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID sceneID)
{
	nextSceneID_ = sceneID;
}
