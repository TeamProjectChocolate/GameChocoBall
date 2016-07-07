#include "stdafx.h"
#include "EnemyBullet.h"
#include "Bullet.h"
#include"Player.h"

//extern CPlayer* g_player;

CEnemyBullet::CEnemyBullet()
{
}

CEnemyBullet::~CEnemyBullet()
{
}

void CEnemyBullet::Initialize(){
	m_enemybullet = SINSTANCE(CObjectManager)->GenerationObject<Bullet>(_T("EnemyBullet"), PRIORTY::BULLET, false);
	m_enemybullet->Initialize();
}

void CEnemyBullet::Update(){
	m_enemybullet->Update();
	BulletPlayerCollision();
}

void CEnemyBullet::Draw(){
	m_enemybullet->Draw();
}


void CEnemyBullet::BulletPlayerCollision(){
		D3DXVECTOR3 dist;
		dist = g_player->GetPos() - m_enemybullet->GetPos();
		float E;
		E = D3DXVec3Length(&dist);//ベクトルの長さを計算
		if (E <= 1)
		{
			//ゲームオーバーつけてねノボリン
			if (!g_player->GetGameover())
			{
				dist /= E;
				g_player->EnemyBulletHit(dist);
			}
			
		}
}
