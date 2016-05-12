#pragma once
#include"BulletPhysics.h"

class  CRigidbody
{
public:
	CRigidbody();
	~CRigidbody();
	void Initialize(D3DXVECTOR3* m_position, D3DXVECTOR3* size);
	void Update(D3DXVECTOR3* m_position);
	void Draw();
	virtual void OnDestroy();
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
private:
	D3DXMATRIX matWorld, m_projMatrix;
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	LPD3DXMESH m_mesh;
	btCollisionShape*	m_collisionShape;	//コリジョンの形状。
	btRigidBody*		m_rigidBody;		//剛体。
	btDefaultMotionState* m_myMotionState;
	D3DXQUATERNION	m_rotation;
	float m_life;
};