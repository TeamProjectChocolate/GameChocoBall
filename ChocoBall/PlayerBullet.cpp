#include "stdafx.h"
#include "PlayerBullet.h"
#include "EnemyManager.h"


CPlayerBullet::CPlayerBullet()
{
}


CPlayerBullet::~CPlayerBullet()
{
}

void CPlayerBullet::Initialize(){
	m_bullet.Initialize();

	m_pEnemyManager = SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager"));
	m_pBlockManager = SINSTANCE(CObjectManager)->FindGameObject<CBuildBlock>(_T("B_Block"));
}

void CPlayerBullet::Update(){
	m_bullet.Update();

	//弾と敵との衝突判定
	BulletEnemyCollision();
	// 弾と壁ギミックの当たり判定
	BulletBlockCollision();
}

void CPlayerBullet::Draw(){
	m_bullet.Draw();
}

void CPlayerBullet::OnDestroy(){
	m_bullet.OnDestroy();
}

void CPlayerBullet::Build(){
	m_bullet.Build();
}

void CPlayerBullet::BulletEnemyCollision(){
	m_lockonEnemyIndex = m_LockOn.FindNearEnemy(m_bullet.GetPos());
	if (m_lockonEnemyIndex != -1){
		EnemyBase* Enemy = m_pEnemyManager->GetEnemy(m_lockonEnemyIndex);
		D3DXVECTOR3 dist;
		dist = Enemy->GetPos() - m_bullet.GetPos();
		float L;
		L = D3DXVec3Length(&dist);//ベクトルの長さを計算

		if (L <= 1)
		{
			//m_Hitflag = true;
			m_pEnemyManager->DeleteEnemy(Enemy);
		}
	}
}

void CPlayerBullet::BulletBlockCollision(){
	if (m_pBlockManager){
		int max_X = m_pBlockManager->GetNum_X();
		int max_Y = m_pBlockManager->GetNum_Y();

		D3DXVECTOR3 dist;
		for (int idx_Y = 0; idx_Y < max_Y; idx_Y++){
			for (int idx_X = 0; idx_X < max_X; idx_X++){
				CBlock* pBlock;
				pBlock = m_pBlockManager->GetBlocks(idx_X, idx_Y);

				dist = pBlock->GetPos() - m_bullet.GetPos();
				float L;
				L = D3DXVec3Length(&dist);//ベクトルの長さを計算
				if (L <= 1.2f)
				{
					pBlock->SetAlive(false);
				}

			}
		}
	}
}
