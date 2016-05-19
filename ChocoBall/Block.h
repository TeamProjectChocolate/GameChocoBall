#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "BulletPhysics.h"
#include "Rigidbody.h"
#include "islntersect.h"



class CBlock : public C3DImage{
public:
	CBlock(){	}
	void Initialize(D3DXVECTOR3 pos);
	void Update();
	void Draw();
	D3DXVECTOR3 GetPos(){
		return m_transform.position;
	}
	void Setradius(float radius)
	{
		m_radius = radius;
	}
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
	void SetLife(bool life){
		m_life = life;
	}
	bool GetLife(){
		return m_life;
	}
private:
	CIsIntersect	m_IsIntersect;
	D3DXVECTOR3		m_moveSpeed;	//�������x
	float			m_radius;
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_collisionShape;	//�R���W�����̌`��B
	btRigidBody*		m_rigidBody;		//���́B
	btDefaultMotionState* m_myMotionState;
	bool m_life;
	CRigidbody			m_RigitBody;
};