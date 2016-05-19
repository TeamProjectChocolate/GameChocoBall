#include "stdafx.h"
#include "ChocoBall.h"

void CChocoBall::Initialize(D3DXVECTOR3 pos)
{
	C3DImage::Initialize();
	m_transform.position = pos;



	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.0f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetAlive(true);

	m_moveSpeed.x = 0.05f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	m_Rigidbody.Initialize(&m_transform.position, &m_transform.scale);


	this->Build(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_transform.position);

	//m_rigidBody->setActivationState(DISABLE_DEACTIVATION);

	//float mass = 1000.0f;

	//btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	//m_rigidBody = new btRigidBody(rbInfo);
	//m_rigidBody->setUserIndex(1);

	//int defState = m_rigidBody->getActivationState();
	//m_rigidBody->setActivationState(defState | DISABLE_DEACTIVATION);



	C3DImage::SetImage();
}


void CChocoBall::Update()
{
	m_Rigidbody.Update(&m_transform.position);
	C3DImage::Update();
}
void CChocoBall::Draw()
{
	SetUpTechnique();
	C3DImage::Draw();
}
void CChocoBall::OnDestroy()
{
	m_Rigidbody.OnDestroy();
}

void CChocoBall::Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos)
{
	//この引数に渡すのはボックスhalfsizeなので、0.5倍する。
	m_collisionShape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	float mass = 0.0f;

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	//m_rigidBody->setUserIndex(1);
	//ワールドに追加。
	g_bulletPhysics.AddRigidBody(m_rigidBody);
}
