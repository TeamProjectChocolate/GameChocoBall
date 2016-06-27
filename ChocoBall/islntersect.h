#pragma once
#include "BulletPhysics.h"
#include "CollisionType.h"
#include "Audio.h"


class CIsIntersect
{
public:
	CIsIntersect();
	~CIsIntersect();
	void CIsIntersect::CollisitionInitialize(D3DXVECTOR3*,float,CollisionType);
	void CIsIntersect::Intersect(D3DXVECTOR3* position, D3DXVECTOR3* m_moveSpeed, bool Jumpflag);
	void CIsIntersect::Intersect2(D3DXVECTOR3* position, D3DXVECTOR3* m_moveSpeed);
	void CIsIntersect::IntersectCamera(D3DXVECTOR3* position, D3DXVECTOR3* moveSpeed);
	bool IsHitGround();
	btRigidBody* GetRigidBody()
	{
		return m_rigidBody;
	}
	btSphereShape* GetSphereShape()
	{
		return m_collisionShape;
	}
	void SetAudio(CAudio* audio){
		m_pAudio = audio;
	}
private:
	//��������BulletPhysics�ŏՓ˔�����s�����߂̃����o�ϐ��B
	btGhostObject*		m_ghostObject;		//!<�S�[�X�g�B���̂̕ς��ɂȂ���́B���S�ɕ��������ɔC���������͍̂��̂��g���B
	btSphereShape*		m_collisionShape;	//!<�R���W�����`��B
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
	CAudio* m_pAudio;

	float			m_radius;			//���a
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x�B
	bool			m_isHitGround;		//�n�ʂɓ��������H
	bool			m_Jumpflag;			//�W�����v�t���O
};
