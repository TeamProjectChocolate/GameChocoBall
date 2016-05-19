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
	D3DXVECTOR3		m_moveSpeed;	//落下速度
	float			m_radius;
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_collisionShape;	//コリジョンの形状。
	btRigidBody*		m_rigidBody;		//剛体。
	btDefaultMotionState* m_myMotionState;
	bool m_life;
	CRigidbody			m_RigitBody;
};