#include "stdafx.h"
#include "EnemyManager.h"
#include "ShadowRender.h"

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
		if (Enemy[i]->GetAlive()){
			Enemy[i]->Update();
		}
		else
		{
			Enemy[i]->OnDestroy();
		}
		
	}
}

void CEnemyManager::Draw()
{
	for (short i = 0; i < numEnemy; i++)
	{
		Enemy[i]->Draw();
	}
}