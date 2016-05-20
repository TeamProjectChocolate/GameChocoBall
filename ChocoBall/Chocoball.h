#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Rigidbody.h"
#include "islntersect.h"


class CChocoBall : public C3DImage {
public:
	CChocoBall(){
		m_collisionShape = nullptr;
		m_rigidBody = nullptr;
		m_myMotionState = nullptr;
		strcpy(m_pFileName, "image/Debri.x");
	}
	~CChocoBall(){}

	void Initialize(D3DXVECTOR3 pos);
	void Update();
	void Draw();
	void OnDestroy();
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
private:
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*		m_collisionShape;	//�R���W�����̌`��B
	btRigidBody*			m_rigidBody;		//���́B
	btDefaultMotionState*	m_myMotionState;
	float					m_life;
	CRigidbody				m_Rigidbody;
	CIsIntersect			m_IsIntersect;
	float					m_radius;
	D3DXVECTOR3				m_moveSpeed;		//�ړ����x�B
};