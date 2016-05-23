#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Rigidbody.h"
#include "islntersect.h"
#include "CourceDef.h"
#include "Turn.h"


class CEnemy : public C3DImage
{
public:
	CEnemy(){
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
private:
	float			m_radius;
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x�B
	D3DXVECTOR3		m_initPosition;		//�������W�B
	float			m_eCurrentAngleY;	//���݂̕���
	float			m_eTargetAngleY;		//������������
	float			m_eTurnSpeed;		//��]���x
	bool			isTurn;				//��]�t���O
	CRigidbody		m_Rigidbody;
	bool			flg;



	CTurn			m_Turn;				//CTurn�̃C���X�^���X
	CIsIntersect	m_IsIntersect;		//CIsIntersect�̃C���X�^���X
	CCourceDef		m_Courcedef;

	D3DXVECTOR3		m_V0;
	D3DXVECTOR3		V1;
	D3DXVECTOR3		V2;
};
