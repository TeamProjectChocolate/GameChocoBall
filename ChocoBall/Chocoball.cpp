#include "stdafx.h"
#include "ChocoBall.h"

void CChocoBall::Initialize(D3DXVECTOR3 Spos, D3DXVECTOR3 Epos)
{
	strcpy(m_pFileName, "image/kyu.x");
	C3DImage::Initialize();
	m_transform.position = Spos; //D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	SetVector(m_transform.position, Epos);
	SetRotation(D3DXVECTOR3(0, 0, 0), 0.1f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rigidbody.Initialize(&m_transform.position, 0.3f);
	
	this->Build(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_transform.position);

	//m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
	m_moveSpeed.x = 0.05f;
	m_moveSpeed.z = 0.05f;
	m_moveSpeed.y = 0.05f;

	//m_radius = 1.0f;

	SetAlive(true);

	SetAlpha(1.0f);
	//m_IsIntersect.CollisitionInitialize(&m_transform.position, m_radius);
	D3DXVec3Normalize(&m_Vector2, &GetVector());

	C3DImage::SetImage();

}


void CChocoBall::Update()
{
	//�����G���W���Ōv�Z���ꂽ���̂̈ʒu�Ɖ�]�𔽉f������B
	//const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();
	//const btQuaternion& rRot = m_rigidBody->getWorldTransform().getRotation();
	//D3DXVECTOR3 pos(rPos.x(), rPos.y(), rPos.z());
	//D3DXQUATERNION rot(rRot.x(), rRot.y(), rRot.z(), rRot.w());
	//
	//m_transform.position.x += rPos.x();
	//m_transform.position.y += rPos.y();
	//m_transform.position.z += rPos.z();

	m_Rigidbody.ApplyForce(m_Vector2 * 5.0f);
//	m_Rigidbody.SetAngularVelocity(D3DXVECTOR3(10.0f, 10.f, 10.0f));
	//SetVector(m_transform.position, m_Vector);
	//m_box.SetPosition(pos);
	//m_box.SetRotation(rot);
	//m_box.UpdateWorldMatrix();
	//m_shadowModel.SetWorldMatrix(m_box.GetWorldMatrix());
	//ShadowMap().Entry(&m_shadowModel);
	//m_life += 1.0f / 60.0f;
	//m_transform.position.y -= 0.05f;
	//btVector3 a(0.0f, 0.0f, 1.0f);

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
}
