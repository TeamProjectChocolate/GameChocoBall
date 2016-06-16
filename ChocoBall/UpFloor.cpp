#include "stdafx.h"
#include "UpFloor.h"


void CUpFloor::Initialize(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	strcpy(m_pFileName, "image/down_block.x");
	C3DImage::Initialize();
	//D3DXMatrixInverse()
	D3DXMATRIX mRot;
	D3DXMatrixRotationQuaternion(&mRot, &rot);
	m_transform.position = pos; //D3DXVECTOR3(0.0f, 0.0f, -45.0f);
	StartPos = m_transform.position;
	SetRotation(D3DXVECTOR3(0, 0, 0), 0.1f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//m_transform.angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_RigitBody.Initialize(&m_transform.position, &m_transform.scale);

	this->Build(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_transform.position);

	m_player = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));

	m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
	//m_moveSpeed.x = 0.0f;
	//m_moveSpeed.z = 0.0f;
	//m_moveSpeed.y = 0.0f;

	//m_radius = 1.0f;

	SetAlive(true);

	//SetAlpha(1.0f);
	//m_IsIntersect.CollisitionInitialize(&m_transform.position, m_radius);

	C3DImage::SetImage();
}


void CUpFloor::Update()
{

	btTransform& trans = m_rigidBody->getWorldTransform();
	trans.setOrigin(btVector3(m_transform.position.x, m_transform.position.y, m_transform.position.z));
	trans.setRotation(btQuaternion(m_transform.angle.x, m_transform.angle.y, m_transform.angle.z));

	D3DXVECTOR3 PlayerPos = m_player->GetPos();

	C3DImage::Update();

	IsHitPlayer(m_transform.position, 1.0f);
	if (IsHitPlayer(m_transform.position, 1.0f))
	{
		if (m_transform.position.y < m_MaxMove){
			m_transform.position.y += 0.1f;
			PlayerPos.y += 0.1f;
			m_player->SetPos(PlayerPos);
		}
	}
	else if (m_transform.position.y < StartPos.y)
	{
		m_transform.position.y -= 0.05f;
	}

}


void CUpFloor::Draw()
{
	SetUpTechnique();
	C3DImage::Draw();
}


void CUpFloor::Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos){
	//���̈����ɓn���̂̓{�b�N�Xhalfsize�Ȃ̂ŁA0.5�{����B
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
	//���[���h�ɒǉ��B
	SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->AddRigidBody(m_rigidBody);
}


bool CUpFloor::IsHitPlayer(D3DXVECTOR3 pos, float radius)
{
	m_WorldMatrix = GetWorldMatrix();
	D3DXMatrixInverse(&m_InvWorld, nullptr, &m_WorldMatrix);


	PlayerPos = m_player->GetPos();

	D3DXVec3Transform(&dimension, &PlayerPos, &m_InvWorld);

	if (fabsf(dimension.x) < 1.0f && fabsf(dimension.z) < 1.0f && dimension.y <= 1.6f)
	{
		return TRUE;
	}
	//D3DXVECTOR3 dist;
	//dist = m_player->GetPos() - pos;
	//float Length;
	//Length = D3DXVec3LengthSq(&dist);

	//if (Length <= radius * radius){
	//	return TRUE;
	//}
	//else
	//{
	//	return FALSE;
	//}
	return FALSE;
}