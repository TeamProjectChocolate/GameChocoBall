#include "stdafx.h"
#include "EnemyManager.h"
#include "ShadowRender.h"

CEnemyManager g_enemyMgr;	//“G‚Ì•Ï”B

void CEnemyManager::Initialize()
{

	for (short i = 0; i < numEnemy; i++)
	{
		Enemy[i]->Initialize();
		SINSTANCE(CShadowRender)->Entry(Enemy[i]);
	}
	SetAlive(true);
}

void CEnemyManager::Update()
{
	for (short i = 0; i < numEnemy; i++)
	{
		Enemy[i]->Update();
	}
}

void CEnemyManager::Draw()
{
	for (short i = 0; i < numEnemy; i++)
	{
		Enemy[i]->Draw();
	}
}