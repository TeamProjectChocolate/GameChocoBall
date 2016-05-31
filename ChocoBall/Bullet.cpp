#include "stdafx.h"

#include "Bullet.h"

Bullet::~Bullet()
{

}

void Bullet::Initialize()
{
	C3DImage::Initialize();
	m_transform.position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	SetRotation(D3DXVECTOR3(0, 0, 1), 0.0f);//弾がZ軸回転する
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetAlive(true);
	SetAlpha(1.0f);//透明度
	//Shotflag = false;
	//m_Hitflag = false;
	m_radius = 1.0f;
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;
	this->Build();
	extern CEnemyManager g_enemyMgr;
	m_IsIntersect.CollisitionInitialize(&m_transform.position, m_radius);
	//m_pPlayer = (SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D")));
	C3DImage::SetImage();

	m_pEnemyManager = SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager"));

	m_pBlockManager = SINSTANCE(CObjectManager)->FindGameObject<CBuildBlock>(_T("B_Block"));
}

void Bullet::Update()
{

	//プレイヤーの向いているベクトルを弾に加算
	m_transform.position.x = m_transform.position.x + m_dir.x*3.0f;
	m_transform.position.y = m_transform.position.y + m_dir.y*3.0f;
	m_transform.position.z = m_transform.position.z + m_dir.z*3.0f;


	//弾と敵との衝突判定
	BulletEnemyCollision();

	// 弾と壁ギミックの当たり判定
	BulletBlockCollision();

	m_IsIntersect.Intersect2(&m_transform.position, &m_moveSpeed);
	C3DImage::Update();
}
void Bullet::Draw()
{
	SetUpTechnique();
	C3DImage::Draw();
}

void Bullet::OnDestroy()
{

}

void Bullet::Build()
{

}

void Bullet::BulletEnemyCollision()
{

	m_lockonEnemyIndex = m_LockOn.FindNearEnemy(m_transform.position);
	if (m_lockonEnemyIndex != -1){
		CEnemy* Enemy = m_pEnemyManager->GetEnemy(m_lockonEnemyIndex);
		D3DXVECTOR3 dist;
		dist = Enemy->GetPos() - m_transform.position;
		float L;
		L = D3DXVec3Length(&dist);//ベクトルの長さを計算

		if (L <= 1)
		{
			//m_Hitflag = true;]
			m_pEnemyManager->DeleteEnemy(Enemy);
		}
	}
}

void Bullet::BulletBlockCollision(){
	int max_X = m_pBlockManager->GetNum_X();
	int max_Y = m_pBlockManager->GetNum_Y();

	D3DXVECTOR3 dist;
	for (int idx_Y = 0; idx_Y < max_Y; idx_Y++){
		for (int idx_X = 0; idx_X < max_X; idx_X++){
			CBlock* pBlock;
			pBlock = m_pBlockManager->GetBlocks(idx_X,idx_Y);

			dist = pBlock->GetPos() - m_transform.position;
			float L;
			L = D3DXVec3Length(&dist);//ベクトルの長さを計算
			if (L <= 1.2f)
			{
				pBlock->SetAlive(false);
			}

		}
	}
}
