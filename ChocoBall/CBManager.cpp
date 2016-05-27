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
		D3DXVECTOR3 pos(GetStartPosition());
		pos.z += fabsf(rate);
		pos.y += rate;
		D3DXVECTOR3 Epos(GetEndPosition());
		Epos.z += fabsf(rate);
		Epos.y += rate;
		m_Choco[i].Initialize(pos, Epos);
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

bool CCBManager::IsHit(D3DXVECTOR3 pos, float radius)
{
	for (int i = 0; i < CHOCO_NUM; i++){
		D3DXVECTOR3 dist;
		dist = m_Choco[i].GetPos() - pos;
		float Length;
		Length = D3DXVec3LengthSq(&dist);
		if (Length <= radius * radius){
			return TRUE;
		}
	}
	return FALSE;
}