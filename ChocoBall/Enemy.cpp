#include "stdafx.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "RenderContext.h"
#include "GameObject.h"
#include "ObjectManager.h"

CEnemy::~CEnemy(){ }

void CEnemy::Initialize()
{
	C3DImage::Initialize();
	m_initPosition = D3DXVECTOR3(18.0f, -0.5f, 18.0f);
	m_transform.position = D3DXVECTOR3(18.0f, -0.5f, 18.0f);
	SetRotation(D3DXVECTOR3(0, 1, 0), 0.1f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_V0 = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_moveSpeed.x = 0.05f;
	m_moveSpeed.z = 0.05f;
	m_moveSpeed.y = 0.05f;
	m_radius = 0.1f;

	m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	SetAlive(true);	//死亡フラグ

	SetAlpha(1.0f);	//透明度？

	flg = true;

	C3DImage::SetImage();
	m_Rigidbody.Initialize(&m_transform.position, &m_transform.scale);

	m_Courcedef.Initialize();

	COURCE_BLOCK Cource = m_Courcedef.FindCource(m_initPosition);
	m_V1 = Cource.endPosition - Cource.startPosition;
	D3DXVec3Normalize(&V1, &m_V1);
	D3DXVec3Cross(&m_V2, &V1, &m_Up);
	D3DXVec3Normalize(&V2, &m_V2);

	extern CEnemyManager g_enemyMgr;
}

void CEnemy::Update()
{
	isTurn = true;

	m_transform.position += V2 * 0.05f;

	m_V3 = m_transform.position - m_initPosition;
	V3 = D3DXVec3Length(&m_V3);

	if (V3 > 2.5)
	{
		V2 *= -1.0f;
	}
	//if (V2 > 0)
	//{
	//	isTurn = true;
	//	//左方向を向かせる
	//	g_targetAngleY = D3DXToRadian(180.0f);
	//}
	//else
	//{
	//	isTurn = false;
	//	//右方向を向かせる。
	//	g_targetAngleY = D3DXToRadian(-180.0f);
	//}
	V0 = D3DXVec3Dot(&m_V0, &V2);
	m_eTargetAngleY=acos(V0);
	D3DXVECTOR3 V4;
	D3DXVec3Cross(&V4, &m_V0, &V2);
	if (V4.y < 0)
	{
		m_eTargetAngleY *= -1.0f;
	}
	m_eCurrentAngleY = m_Turn.Update(isTurn, m_eTargetAngleY);

	// 回転行列
	SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_eCurrentAngleY);
	C3DImage::Update();
}


void CEnemy::Draw()
{
	IMAGE3D* img = GetImage();
	m_Rigidbody.Draw();
	SetUpTechnique();
	C3DImage::Draw();
	
}

void CEnemy::OnDestroy()
{
	m_Rigidbody.OnDestroy();
}

void CEnemy::Build()
{
	m_Rigidbody.Build(m_transform.scale, m_transform.position);
}
