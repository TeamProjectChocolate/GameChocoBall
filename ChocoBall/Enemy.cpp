#include "stdafx.h"
#include "EnemyManager.h"
#include "RenderContext.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "Player.h"
#include "InputManager.h"

extern CEnemyManager g_enemyMgr;
extern CPlayer* g_player;

CEnemy::CEnemy()
{
	m_initPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_transform.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	strcpy(m_pFileName, "image/ENr.x");
};

CEnemy::~CEnemy(){ }
D3DXVECTOR3 CEnemy::GetPos(){
	return m_transform.position;
}
void CEnemy::Setradius(float radius)
{
	m_radius = radius;
}
void CEnemy::SetInitPosition(D3DXVECTOR3 pos)
{
	m_initPosition = pos;
	m_transform.position = pos;
}
void CEnemy::Initialize()
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
	SetAlive(true);	//���S�t���O
	SetAlpha(1.0f);	//�����x�H
	flg = true;
	C3DImage::SetImage();

	m_Courcedef.SetStageID(m_StageID);
	m_Courcedef.Initialize();
	COURCE_BLOCK Cource = m_Courcedef.FindCource(m_initPosition);

	m_V1 = Cource.endPosition - Cource.startPosition;					//�X�^�[�g����S�[���Ɍ����Ẵx�N�g��
	D3DXVec3Normalize(&V1, &m_V1);										//��ŋ��߂��x�N�g���̐��K��
	D3DXVec3Cross(&m_V2, &V1, &m_Up);
	D3DXVec3Normalize(&V2, &m_V2);

	m_pPlayer = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));
	m_pInput = SINSTANCE(CInputManager)->GetCurrentInput();
}

void CEnemy::Update()
{

	SINSTANCE(CInputManager)->IsInputChanged(&m_pInput);


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
	//��]�s��
	SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_eCurrentAngleY);
	EnemyBulletShot();
	C3DImage::Update();
}


void CEnemy::Draw()
{
	if (GetAlive())
	{
		//IMAGE3D* img = GetImage();
		m_Rigidbody.Draw();
		SetUpTechnique();
		C3DImage::Draw();
	}

	int size = m_bullets.size();
	for (int idx = 0; idx < size; idx++){
		m_bullets[idx]->Draw();
	}
	ExcuteDeleteBullets();
}

void CEnemy::OnDestroy()
{
	m_Rigidbody.OnDestroy();
	SetAlive(false);
}

void CEnemy::Build()
{
	m_Rigidbody.Build(m_transform.scale, m_transform.position);
}
void CEnemy::EnemyBulletShot()
{
	if (m_pInput->IsTriggerRightShift())
	{

		//�G�l�~�[�̌����x�N�g�����v�Z
		D3DXVECTOR3 EnemyToPlayerVec = m_pPlayer->GetPos() - m_transform.position;
		if (50.0f >= D3DXVec3Length(&EnemyToPlayerVec)){
			D3DXVec3Normalize(&EnemyToPlayerVec, &EnemyToPlayerVec);
		}

		CEnemyBullet* bullet = new CEnemyBullet;
		bullet->Initialize();
		bullet->SetPos(m_transform.position);
		D3DXVECTOR4 work;
		work.x = EnemyToPlayerVec.x;
		work.y = EnemyToPlayerVec.y;
		work.z = EnemyToPlayerVec.z;
		work.w = 0.0f;
		bullet->SetDir(work);
		bullet->SetBulletSpeed(1.0f);//�G�̒e�̑��x
		m_bullets.push_back(bullet);
	}

	//�G�l�~�[�ƒe�̋�����30m�ɂȂ�ƒe��������Delete����B
	int size = m_bullets.size();
	for (int idx = 0; idx < size; idx++){
		D3DXVECTOR3 V5;
		V5 = m_bullets[idx]->GetPos() - m_transform.position;
		float length = D3DXVec3Length(&V5);
		length = fabs(length);
		if (length > 50.0f)
		{
			EnemyDeleteBullet(m_bullets[idx]);
		}
		else{
			m_bullets[idx]->Update();
		}
	}
}

void CEnemy::EnemyDeleteBullet(CEnemyBullet* bullet){
	m_Deletebullets.push_back(bullet);
}

void CEnemy::ExcuteDeleteBullets(){
	vector<CEnemyBullet*>::iterator itr;
	int size = m_Deletebullets.size();
	for (int idx = 0; idx < size; idx++){
		for (itr = m_bullets.begin(); itr != m_bullets.end();){
			if (m_Deletebullets[idx] == *itr){
				SAFE_DELETE(*itr);
				itr = m_bullets.erase(itr);
				break;
			}
			else{
				itr++;
			}
		}
	}
	m_Deletebullets.clear();
}