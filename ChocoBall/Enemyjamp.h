#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Rigidbody.h"
#include "islntersect.h"
#include "CourceDef.h"
#include "Turn.h"
#include "EnemyBase.h"

class CEnemyjamp : public EnemyBase
{
public:
	CEnemyjamp();
	~CEnemyjamp();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	D3DXVECTOR3 GetPos();
	void Setradius(float radius)
	{
		m_radius = radius;
	}
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
	D3DXVECTOR3 m_Up;
};
