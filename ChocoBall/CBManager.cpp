#include "stdafx.h"
#include "Chocoball.h"
#include "CBManager.h"


void CCBManager::Initialize()
{
	for (int i = 0; i < CHOCO_NUM; i++)
	{
		D3DXVECTOR3	pos(0.0f, 5.0f, -15.0f);
		m_Choco[i].Initialize(pos/*GetPosition()*/);
	}
	SetAlive(true);
}

void CCBManager::Update()
{
	for (int i = 0; i < CHOCO_NUM; i++)
	{
		m_Choco[i].Update();

	}
}

void CCBManager::Draw()
{
	for (int i = 0; i < CHOCO_NUM; i++)
	{
		m_Choco[i].Draw();
	}
}