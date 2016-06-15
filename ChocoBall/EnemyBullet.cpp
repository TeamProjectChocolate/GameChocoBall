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
	m_enemybullet.Initialize();
}

void CEnemyBullet::Update(){
	m_enemybullet.Update();
	BulletPlayerCollision();
}

void CEnemyBullet::Draw(){
	m_enemybullet.Draw();
}

void CEnemyBullet::OnDestroy(){
	m_enemybullet.OnDestroy();
}

void CEnemyBullet::Build(){
	m_enemybullet.Build();
}

void CEnemyBullet::BulletPlayerCollision(){
		D3DXVECTOR3 dist;
		dist = g_player->GetPos() - m_enemybullet.GetPos();
		float E;
		E = D3DXVec3Length(&dist);//�x�N�g���̒������v�Z
		if (E <= 1)
		{
			//�Q�[���I�[�o�[���Ă˃m�{����
			if (!g_player->GetGameover())
			{
				dist /= E;
				g_player->EnemyBulletHit(dist);
			//	g_player->RollingPlayer();
			//	g_player->RequestGameOver();
			}
			
		}
}
