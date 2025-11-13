#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Engine/SphereCollider.h"
#include "Bullet.h"
#include "Bar.h"


PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	Instanitiate<Player>(this);

	// EnemyÇê∂ê¨
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
