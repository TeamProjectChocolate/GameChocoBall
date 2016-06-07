#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Rigidbody.h"
#include "islntersect.h"


class CDebri : public C3DImage {
public:
	CDebri(){
		m_collisionShape = nullptr;
		//m_rigidBody = nullptr;
		m_myMotionState = nullptr;
		strcpy(m_pFileName, "image/Debri.x");
	}
	~CDebri(){}

	void Initialize();
	void Update();
	void Draw();
	void OnDestroy();
	void Build();
private:
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_collisionShape;	//�R���W�����̌`��B
	//btRigidBody*		m_rigidBody;		//���́B
	btDefaultMotionState* m_myMotionState;
	float m_life;
	//CRigidbody m_Rigidbody;
	//CIsIntersect m_IsIntersect;
	float			m_radius;
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x�B
};