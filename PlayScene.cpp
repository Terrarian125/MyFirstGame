#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine/SphereCollider.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//Player‚ğ¶¬‚µ‚ÄAq‚É’Ç‰Á
	//Player* pPlayer;
	//pPlayer = new Player(this);
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);
	Instanitiate<Player>(this);

	// Enemy‚ğ¶¬
	Instanitiate<Enemy>(this);
	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
