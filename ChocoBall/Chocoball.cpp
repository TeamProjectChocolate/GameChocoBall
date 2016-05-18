#include "stdafx.h"
#include "Chocoball.h"
#include "ShadowRender.h"


void CChocoball::Initialize(D3DXVECTOR3 pos)
{
	strcpy(m_pFileName, "image/BR.x");
	C3DImage::Initialize();
	m_transform.position = pos;
	SetRotation(D3DXVECTOR3(0, 0, 0), 0.1f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_RigitBody.Initialize(&m_transform.position, &m_transform.scale);


	this->Build(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_transform.position);

	m_rigidBody->setActivationState(DISABLE_DEACTIVATION);

	C3DImage::SetImage();
}

void CChocoball::Update()
{
	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();
	const btQuaternion& rRot = m_rigidBody->getWorldTransform().getRotation();
	D3DXVECTOR3 pos(rPos.x(), rPos.y(), rPos.z());
	D3DXQUATERNION rot(rRot.x(), rRot.y(), rRot.z(), rRot.w());
	m_RigitBody.Update(&m_transform.position);
	m_transform.position.x = rPos.x();
	m_transform.position.y = rPos.y();
	m_transform.position.z = rPos.z();
	//m_box.SetPosition(pos);
	//m_box.SetRotation(rot);
	//m_box.UpdateWorldMatrix();
	//m_shadowModel.SetWorldMatrix(m_box.GetWorldMatrix());
	//ShadowMap().Entry(&m_shadowModel);
	//m_life += 1.0f / 60.0f;
	//m_transform.position.y -= 0.05f;
	//btVector3 a(0.0f, 0.0f, 1.0f);


	C3DImage::Update();
}

void CChocoball::Draw()
{
	SetUpTechnique();
	C3DImage::Draw();
}


void CChocoball::Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos)
{
	m_collisionShape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	float mass = 1000.0f;

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	//m_rigidBody->setUserIndex(1);
	//ƒ[ƒ‹ƒh‚É’Ç‰ÁB
	g_bulletPhysics.AddRigidBody(m_rigidBody);
}