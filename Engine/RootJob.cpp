#include "RootJob.h"
#include "..\\PlayScene.h"
#include "SceneManager.h"

RootJob::RootJob(GameObject* parent)
	:GameObject(parent, "RootJob")
{
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	Instanitiate<SceneManager>(this);
}

void RootJob::Update()
{
}

void RootJob::Draw()
{
}

void RootJob::Release()
{
}
