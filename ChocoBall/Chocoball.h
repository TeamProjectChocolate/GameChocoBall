#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "BulletPhysics.h"
#include "Rigidbody.h"
#include "islntersect.h"
#include "ObjectManager.h"

class CChocoball : C3DImage {
public:
	CChocoball(){
		SetLife(true);
	}
	void Initialize(D3DXVECTOR3 pos);
	void Update();
	void Draw();
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
	void SetLife(bool life)
	{
		m_Life = life;
	}
	void SetVector(D3DXVECTOR3 vec)
	{
		m_cVector = vec;
	}

private:
	D3DXVECTOR3			m_cVector;			//�`���R�{�[���̐i�s����
	D3DXVECTOR3			m_moveSpeed;		//�ړ����x
	bool				m_Life;
	btRigidBody*		m_rigidBody;
	CRigidbody			m_RigitBody;
	btCollisionShape*	m_collisionShape;	//�R���W�����̌`��B
	btDefaultMotionState* m_myMotionState;

};