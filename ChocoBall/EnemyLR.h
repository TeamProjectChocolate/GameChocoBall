#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Rigidbody.h"
#include "islntersect.h"
#include "CourceDef.h"
#include "Turn.h"
#include "EnemyBase.h"

class CEnemyLR : public EnemyBase
{
public:
	CEnemyLR();
	~CEnemyLR();
	void Initialize()override; 
	void Update()override;
	void Draw()override;
	void OnDestroy();
	void Build();
	D3DXVECTOR3 GetPos();
	void Setradius(float radius);
	void SetInitPosition(D3DXVECTOR3 pos);

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
	bool			m_Hitflag;

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
