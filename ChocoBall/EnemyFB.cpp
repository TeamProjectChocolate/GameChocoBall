#include "stdafx.h"
#include "EnemyFB.h"
#include "EnemyManager.h"
#include "RenderContext.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "Player.h"
#include "InputManager.h"

extern CEnemyManager g_enemyMgr;
extern CPlayer* g_player;

CEnemyFB::CEnemyFB()
{
	m_initPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_transform.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	strcpy(m_pFileName, "image/ENr.x");
};

CEnemyFB::~CEnemyFB(){ }

void CEnemyFB::Initialize()
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
	SetAlive(true);	//���S�t���O
	SetAlpha(1.0f);	//�����x�H
	flg = true;
	C3DImage::SetImage();
	m_Rigidbody.Initialize(&m_transform.position, &m_transform.scale);

	m_Courcedef.Initialize();
	COURCE_BLOCK Cource = m_Courcedef.FindCource(m_initPosition);

	m_V1 = Cource.endPosition - Cource.startPosition;					//�X�^�[�g����S�[���Ɍ����Ẵx�N�g��
	D3DXVec3Normalize(&V1, &m_V1);										//��ŋ��߂��x�N�g���̐��K��
	D3DXVec3Cross(&m_V2, &V1, &m_Up);
	D3DXVec3Normalize(&V2, &m_V2);

	extern CEnemyManager g_enemyMgr;
}

void CEnemyFB::SetUpTechnique()
{
	m_pEffect->SetTechnique("TextureTec");
}
D3DXVECTOR3 CEnemyFB::GetPos(){
	return m_transform.position;
}
void CEnemyFB::SetInitPosition(D3DXVECTOR3 pos)
{
	m_initPosition = pos;
	m_transform.position = pos;
}
void CEnemyFB::Update()
{
	isTurn = true;

	m_transform.position += V1*0.05f;
	D3DXVECTOR3 v = m_transform.position - m_initPosition;
	float v1 = D3DXVec3Length(&v);
	if (v1 > 2.5){
		V1 *= -1.0f;
	}

	C3DImage::Update();
}


void CEnemyFB::Draw()
{
	if (GetAlive())
	{
		//IMAGE3D* img = GetImage();
		m_Rigidbody.Draw();
		SetUpTechnique();
		C3DImage::Draw();
	}
}

void CEnemyFB::OnDestroy()
{
	m_Rigidbody.OnDestroy();
	SetAlive(false);
}

void CEnemyFB::Build()
{
	m_Rigidbody.Build(m_transform.scale, m_transform.position);
}
