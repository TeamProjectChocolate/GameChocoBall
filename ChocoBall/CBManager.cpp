#include "stdafx.h"
#include "Chocoball.h"
#include "CBManager.h"
#include "ShadowRender.h"


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
			float rate = 100.0f / (rand() % 100 + 1);
			rate /= 50.0f;
			if (rand() % 2){
				rate *= -1.0f;
			}
			D3DXVECTOR3 pos(GetStartPosition());
			pos.x += rate;
			pos.z += fabsf(rate);
			pos.y += rate;
			D3DXVECTOR3 Epos(GetEndPosition());
			Epos.x += rate;
			Epos.z += fabsf(rate);
			Epos.y += rate;
			m_Choco[m_numCreate].Initialize(pos, Epos);
			SINSTANCE(CShadowRender)->Entry(&m_Choco[m_numCreate]);
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

bool CCBManager::IsHit(D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	for (int i = 0; i < m_numCreate; i++){
		//プレイヤーを内包する箱の最大値と最小値を求める。
		D3DXVECTOR3 MaxSize;//最大値
		D3DXVECTOR3 MinSize;//最小値
		const static float Sphereradius = 0.5f;//チョコボールの半径
		size *= 0.5f;
		MaxSize.x = pos.x + size.x + Sphereradius;
		MaxSize.y = pos.y + size.y + Sphereradius;
		MaxSize.z = pos.z + size.z + Sphereradius;

		MinSize.x = pos.x - size.x - Sphereradius;
		MinSize.y = pos.y - size.y - Sphereradius;
		MinSize.z = pos.z - size.z - Sphereradius;
		D3DXVECTOR3 chocoPos = m_Choco[i].GetPos();
		//プレイヤーにチョコボールの半径分を足した箱内に入っている弾との当たり判定を調べる。
		if (MinSize.x < chocoPos.x&&
			MinSize.y < chocoPos.y&&
			MinSize.z < chocoPos.z&&
			chocoPos.x < MaxSize.x&&
			chocoPos.y < MaxSize.y&&
			chocoPos.z < MaxSize.z)
		{
			return TRUE;
		}
	
	}
	return FALSE;
}