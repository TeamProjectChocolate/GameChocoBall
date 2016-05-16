#include "stdafx.h"
#include "Debri.h"

void CDebri::Initialize()
{
	C3DImage::Initialize();
	m_transform.position = D3DXVECTOR3(0.0f,4.0f,0.0f);
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 1.0f), 0.0f);
	m_transform.scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	SetAlive(true);
	
	m_moveSpeed.x = 0.05f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	m_Rigidbody.Initialize(&m_transform.position, &m_transform.scale);

	//m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
	
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
