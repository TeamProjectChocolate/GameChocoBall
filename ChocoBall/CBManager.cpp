#include "stdafx.h"
#include "Chocoball.h"
#include "CBManager.h"


void CCBManager::Initialize()
{
	m_interval = 0.2f;
	m_timer = 0.0f;
	m_numCreate = 0;
	/*for (int i = 0; i < CHOCO_NUM; i++)
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
	}*/
	SetAlive(true);
}

void CCBManager::Update()
{
	//チョコボールを生成していく。
	const float deltaTime = 1.0f / 60.0f;
	m_timer += deltaTime;
	if (m_interval < m_timer){
		int createCount = 0;
		while ( m_numCreate < CHOCO_NUM ){
			if (createCount == 10){
				break;
			}
			int rate = 100.0f / (rand() % 100 + 1);
			if (rand() % 2){
				rate *= -1.0f;
			}
			D3DXVECTOR3 pos(GetStartPosition());
			pos.z += fabsf(rate);
			pos.y += rate;
			D3DXVECTOR3 Epos(GetEndPosition());
			Epos.z += fabsf(rate);
			Epos.y += rate;
			m_Choco[m_numCreate].Initialize(pos, Epos);
			createCount++;
			m_numCreate++;
		}
	}
	for (int i = 0; i < m_numCreate; i++)
	{
		m_Choco[i].Update();
	}
}

void CCBManager::Draw()
{
	for (int i = 0; i < m_numCreate; i++)
	{
		m_Choco[i].Draw();
	}
}

bool CCBManager::IsHit(D3DXVECTOR3 pos, float radius)
{
	for (int i = 0; i < m_numCreate; i++){
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