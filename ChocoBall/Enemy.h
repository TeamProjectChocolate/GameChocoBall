#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Rigidbody.h"
#include "islntersect.h"
#include "CourceDef.h"
#include "Turn.h"
#include "GameManager.h"
#include "Bullet.h"

class CEnemy : public C3DImage
{
public:
	CEnemy(){
		m_initPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_transform.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
		strcpy(m_pFileName, "image/ENr.x");
	};
	~CEnemy();
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("TextureTec");
	}

	void Initialize()override; 
	void Update()override;
	void Draw()override;
	void OnDestroy();
	void Build();
	D3DXVECTOR3 GetPos(){
		return m_transform.position;
	}
	void Setradius(float radius)
	{
		m_radius = radius;
	}
	void SetInitPosition(D3DXVECTOR3 pos)
	{
		m_initPosition = pos;
		m_transform.position = pos;
	}
private:	
	CInterface*	m_pInput;

	float			m_radius;
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x�B
	D3DXVECTOR3		m_initPosition;		//�������W�B
	float			m_eCurrentAngleY;	//���݂̕���
	float			m_eTargetAngleY;		//������������
	float			m_eTurnSpeed;		//��]���x
	bool			isTurn;				//��]�t���O
	CRigidbody		m_Rigidbody;
	bool			flg;
	bool			m_Hitflag;
	Bullet*         m_pBullet;
	CTurn			m_Turn;				//CTurn�̃C���X�^���X
	CIsIntersect	m_IsIntersect;		//CIsIntersect�̃C���X�^���X
	CCourceDef		m_Courcedef;

	D3DXVECTOR3		m_V0;
	float V0;
	D3DXVECTOR3		V1;
	D3DXVECTOR3 m_V1;
	D3DXVECTOR3		V2;
	D3DXVECTOR3		m_V2;
	D3DXVECTOR3 m_V3;
	float V3;
	D3DXVECTOR3 m_Up;
};
