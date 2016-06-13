#include "stdafx.h"
#include "EnemyBullet.h"
#include "Bullet.h"
#include"Player.h"

extern CPlayer* g_player;



CEnemyBullet::CEnemyBullet()
{
}

CEnemyBullet::~CEnemyBullet()
{
}

void CEnemyBullet::Initialize(){
	m_bullet.Initialize();
}

void CEnemyBullet::Update(){
	m_bullet.Update();
	BulletPlayerCollision();
}

void CEnemyBullet::Draw(){
	m_bullet.Draw();
}

void CEnemyBullet::OnDestroy(){
	m_bullet.OnDestroy();
}

void CEnemyBullet::Build(){
	m_bullet.Build();
}

void CEnemyBullet::BulletPlayerCollision(){
		D3DXVECTOR3 dist;
		dist = g_player->GetPos() - m_bullet.GetPos();
		float L;
		L = D3DXVec3Length(&dist);//ベクトルの長さを計算

		if (L <= 1)
		{
			//ゲームオーバーつけてねノボリン！
		}
	
}