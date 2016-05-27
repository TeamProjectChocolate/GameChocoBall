#include "stdafx.h"

#include "Bullet.h"
#include "Player.h"
#include "EnemyManager.h"

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
	Shotflag = false;
	m_Hitflag = false;
	m_radius = 1.0f;
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;
	this->Build();
	extern CEnemyManager g_enemyMgr;
	m_IsIntersect.CollisitionInitialize(&m_transform.position, m_radius);
	//m_pPlayer = (SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D")));
	C3DImage::SetImage();
}

void Bullet::Update()
{

	//プレイヤーの向いているベクトルを弾に加算
	m_transform.position.x = m_transform.position.x + m_dir.x*3.0f;
	m_transform.position.y = m_transform.position.y + m_dir.y*3.0f;
	m_transform.position.z = m_transform.position.z + m_dir.z*3.0f;


	//弾と敵との衝突判定
	BulletEnemyCollision();

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
	m_Rigidbody.OnDestroy();
}

void Bullet::Build()
{
	m_Rigidbody.Build(m_transform.scale, m_transform.position);
}

void Bullet::BulletEnemyCollision()
{
	CEnemyManager* EnemyManager = (SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager")));
	m_lockonEnemyIndex = m_LockOn.FindNearEnemy(m_transform.position);
	CEnemy* Enemy = EnemyManager->GetEnemy(m_lockonEnemyIndex);
	D3DXVECTOR3 dist;
	dist = Enemy->GetPos() - m_transform.position;
	float L;
	L = D3DXVec3Length(&dist);//ベクトルの長さを計算
	if (L <= 1)
	{
		m_Hitflag = true;
		Enemy->SetAlive
			(false);
	}
}

void Bullet::BulletPlayerCollision()
{
	
}