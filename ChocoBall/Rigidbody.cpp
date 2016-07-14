#include "stdafx.h"
#include "Rigidbody.h"
#include "Objectmanager.h"

CRigidbody::CRigidbody()
{

}

CRigidbody::~CRigidbody()
{

}

void CRigidbody::Initialize(D3DXVECTOR3* m_position, D3DXVECTOR3* size)
{
	D3DXMatrixIdentity(&matWorld);
	m_life = 0.0f;
	Build(*size, *m_position);
	m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
}
void CRigidbody::Initialize(D3DXVECTOR3* m_position, float radius)
{
	D3DXMatrixIdentity(&matWorld);
	m_life = 0.0f;
	Build(radius, *m_position);
	m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
}
void CRigidbody::Update(D3DXVECTOR3* m_position)
{
	//�����G���W���Ōv�Z���ꂽ���̂̈ʒu�Ɖ�]�𔽉f������B
	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();
	const btQuaternion& rRot = m_rigidBody->getWorldTransform().getRotation();
	m_position->x = rPos.x();
	m_position->y = rPos.y();
	m_position->z = rPos.z();
	//D3DXVECTOR3 axis(0.707f, -0.707f, 0.0f);
	//D3DXQuaternionRotationAxis(&m_rotation, &axis, D3DXToRadian(45.0f));
	m_rotation.x = rRot.x();
	m_rotation.y = rRot.y();
	m_rotation.z = rRot.z();
	m_rotation.w = rRot.w();
}

void CRigidbody::Draw()
{
	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationQuaternion(
		&rotMatrix,
		&m_rotation
		);
	D3DXMatrixMultiply(&matWorld, &rotMatrix, &matWorld);
}

void CRigidbody::OnDestroy()
{
	if (m_rigidBody){
		SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->RemoveRigidBody(m_rigidBody);
	}
	delete m_myMotionState;
	delete m_collisionShape;
	delete m_rigidBody;
	m_myMotionState = NULL;
	m_collisionShape = NULL;
	m_rigidBody = NULL;
}
/*!
*@brief	�\�z�����B
*@param[in]	size	���̃T�C�Y�B
*@param[in]	pos		���̍��W�B
*/
void CRigidbody::Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos)
{
	//���̈����ɓn���̂̓{�b�N�Xhalfsize�Ȃ̂ŁA0.5�{����B
	m_collisionShape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	float mass = 1.0f;

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserIndex(1);
	//���[���h�ɒǉ��B
	SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->AddRigidBody(m_rigidBody);

}
/*!
*@brief	�\�z�����B
*@param[in]	radius	���̔��a�B
*@param[in]	pos		���̍��W�B
*/
void CRigidbody::Build(float radius, const D3DXVECTOR3& pos)
{
	//���̈����ɓn���̂̓{�b�N�Xhalfsize�Ȃ̂ŁA0.5�{����B
	m_collisionShape = new btSphereShape(radius);
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	float mass = 1.0f;

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserIndex(1);
	//���[���h�ɒǉ��B
	SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->AddRigidBody(m_rigidBody);

}