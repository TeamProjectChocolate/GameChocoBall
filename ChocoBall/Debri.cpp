#include "stdafx.h"
#include "Debri.h"

void CDebri::Initialize()
{

	m_transform.position = D3DXVECTOR3(0.0f,4.0f,0.0f);
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.0f);
	m_transform.scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	SetAlive(true);
	m_Rigidbody.Initialize(&m_transform.position, &m_transform.scale);

	this->Build();

	//float mass = 1000.0f;

	//btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	//m_rigidBody = new btRigidBody(rbInfo);
	//m_rigidBody->setUserIndex(1);

	//int defState = m_rigidBody->getActivationState();
	//m_rigidBody->setActivationState(defState | DISABLE_DEACTIVATION);

	C3DImage::Initialize();
	C3DImage::SetImage();
}


void CDebri::Update()
{
	m_Rigidbody.Update(&m_transform.position);
	C3DImage::Update();
}
void CDebri::Draw()
{
	SetUpTechnique();
	m_Rigidbody.Draw();
	C3DImage::Draw();
}
void CDebri::OnDestroy()
{
	m_Rigidbody.OnDestroy();
}

void CDebri::Build()
{
	m_Rigidbody.Build(m_transform.scale,m_transform.position);
}
