#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine/SphereCollider.h"
#include "Bullet.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//Playerを生成して、子に追加
	//Player* pPlayer;
	//pPlayer = new Player(this);
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);
	Instanitiate<Player>(this);

	// Enemyを生成
	Instanitiate<Enemy>(this);
	//SphereCollider* col = new SphereCollider(0.5f);
	//AddCollider(col);
}

void PlayScene::Update()
{
	//スペースキーが押されたらBulletを生成してとばす

}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
