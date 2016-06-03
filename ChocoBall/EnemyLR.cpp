#include "stdafx.h"
#include "EnemyManager.h"
#include "RenderContext.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "Player.h"
#include "InputManager.h"

extern CEnemyManager g_enemyMgr;
extern CPlayer* g_player;

CEnemyLR::CEnemyLR()
{
	m_initPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_transform.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	strcpy(m_pFileName, "image/ENr.x");
};

CEnemyLR::~CEnemyLR(){ }
void CEnemyLR::SetUpTechnique(){
	m_pEffect->SetTechnique("TextureTec");
}
D3DXVECTOR3 CEnemyLR::GetPos(){
	return m_transform.position;
}
void CEnemyLR::Setradius(float radius)
{
	m_radius = radius;
}
void CEnemyLR::SetInitPosition(D3DXVECTOR3 pos)
{
	m_initPosition = pos;
	m_transform.position = pos;
}
void CEnemyLR::Initialize()
{
	C3DImage::Initialize();
	SetRotation(D3DXVECTOR3(0, 1, 0), 0.1f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_V0 = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_moveSpeed.x = 0.05f;
	m_moveSpeed.z = 0.05f;
	m_moveSpeed.y = 0.05f;
	m_radius = 0.1f;
	m_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//m_Hitflag = false;
	SetAlive(true);	//死亡フラグ
	SetAlpha(1.0f);	//透明度？
	flg = true;
	C3DImage::SetImage();
	m_Rigidbody.Initialize(&m_transform.position, &m_transform.scale);

	m_Courcedef.Initialize();
	COURCE_BLOCK Cource = m_Courcedef.FindCource(m_initPosition);
	
	m_V1 = Cource.endPosition - Cource.startPosition;					//スタートからゴールに向けてのベクトル
	D3DXVec3Normalize(&V1, &m_V1);										//上で求めたベクトルの正規化
	D3DXVec3Cross(&m_V2, &V1, &m_Up);
	D3DXVec3Normalize(&V2, &m_V2);

	//extern CEnemyManager g_enemyMgr;
}

void CEnemyLR::Update()
{
	isTurn = true;

	m_transform.position += V2 * 0.05f;
	m_V3 = m_transform.position - m_initPosition;
	V3 = D3DXVec3Length(&m_V3);
	if (V3 > 2.5)
	{
		V2 *= -1.0f;
	}

	V0 = D3DXVec3Dot(&m_V0, &V2);
	m_eTargetAngleY = acos(V0);
	D3DXVECTOR3 V4;
	D3DXVec3Cross(&V4, &m_V0, &V2);
	if (V4.y < 0)
	{
		m_eTargetAngleY *= -1.0f;
	}
	m_eCurrentAngleY = m_Turn.Update(isTurn, m_eTargetAngleY);
	//回転行列
	SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_eCurrentAngleY);

	C3DImage::Update();
}


void CEnemyLR::Draw()
{
	if (GetAlive())
	{
		//IMAGE3D* img = GetImage();
		m_Rigidbody.Draw();
		SetUpTechnique();
		C3DImage::Draw();
	}
}

void CEnemyLR::OnDestroy()
{
	m_Rigidbody.OnDestroy();
	SetAlive(false);
}

void CEnemyLR::Build()
{
	m_Rigidbody.Build(m_transform.scale, m_transform.position);
}

