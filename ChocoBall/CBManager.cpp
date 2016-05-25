#include "stdafx.h"
#include "Chocoball.h"
#include "CBManager.h"


void CCBManager::Initialize()
{
	for (int i = 0; i < CHOCO_NUM; i++)
	{
		int rate = 100.0f / (rand() % 100+1);
		if (rand() % 2){
			rate *= -1.0f;
		}
		D3DXVECTOR3	pos(0.0f, rate, -50.0f + fabsf(rate));
		D3DXVECTOR3 Epos(0.0f, -1.0f, 0.0f);
		SetStartPosition(pos);
		SetEndPosition(Epos);
		m_Choco[i].Initialize(GetStartPosition(), GetEndPosition());
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