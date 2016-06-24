#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Rigidbody.h"
#include "islntersect.h"


class CChocoBall : public C3DImage {
public:
	CChocoBall(){  }
	~CChocoBall(){}

	void Initialize(D3DXVECTOR3 Spos, D3DXVECTOR3 Epos);
	void Update();
	void Draw();
	virtual void SetUpTechnique()override{
		m_pEffect->SetTechnique("NotNormalMapNonAnimationFresnelTec");
	}
	void OnDestroy();

	D3DXVECTOR3 GetPos()
	{
		return m_transform.position;
	}

	//�����_�ƖړI�n��n���ƃx�N�g�����Z�b�g���܂��B
	//GetVector()�ŌĂяo���Ă��������B
	void SetVector(D3DXVECTOR3 Spos, D3DXVECTOR3 Epos){
		m_Vector = Epos - Spos;
	}

	//�x�N�g����Ԃ���I
	D3DXVECTOR3 GetVector()
	{
		return m_Vector;
	}

private:
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*		m_collisionShape;	//�R���W�����̌`��B
	D3DXVECTOR3				m_EndPosition;		//�ړI�n
	D3DXVECTOR3				m_Vector;			//�i�s�������i�[�B
	D3DXVECTOR3				m_Vector2;
	btDefaultMotionState*	m_myMotionState;
	float					m_life;
	CRigidbody				m_Rigidbody;
	CIsIntersect			m_IsIntersect;
	float					m_radius;
	D3DXVECTOR3				m_moveSpeed;		//�ړ����x�B
	
};