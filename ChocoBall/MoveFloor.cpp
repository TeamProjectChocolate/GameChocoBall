#include "stdafx.h"
#include "MoveFloor.h"

MoveFloor::MoveFloor()
{
	m_player = NULL;

}

MoveFloor::~MoveFloor()
{
	
}

void MoveFloor::Initialize(D3DXVECTOR3 pos, D3DXQUATERNION rot, D3DXVECTOR3 scale)
{
	strcpy(m_pFileName, "image/down_block.x");
	C3DImage::Initialize();
	//D3DXMatrixInverse()
	m_transform.position = pos;//D3DXVECTOR3(0.0f, 0.0f, -40.0f);
	StartPos = m_transform.position;
	SetRotation(D3DXVECTOR3(0, 0, 0), 0.1f);
	m_transform.scale = scale;// D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_transform.angle = rot;
	m_state = move_flont;
	m_MoveSpeed = D3DXVECTOR3(0.0f,0.0f,0.05f);
	this->Build(D3DXVECTOR3(1.5f * scale.x, 0.3f * scale.y, 1.5f * scale.z), m_transform.position);

	m_player = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));

	m_rigidBody->setActivationState(DISABLE_DEACTIVATION);

	SetAlive(true);

	//SetAlpha(1.0f);
	//m_IsIntersect.CollisitionInitialize(&m_transform.position, m_radius);

	C3DImage::SetImage();
}


void MoveFloor::Update()
{
	btTransform& trans = m_rigidBody->getWorldTransform();
	trans.setOrigin(btVector3(m_transform.position.x, m_transform.position.y, m_transform.position.z));

	float length = D3DXVec3Length(&(m_transform.position - StartPos));
	D3DXVECTOR3 PlayerPos = m_player->GetPos();
	if (MaxMove == 0.0f){
		m_state = move_none;
	}
	else if (length/*fabsf(m_transform.position.z) - fabsf(StartPos.z)*/ > MaxMove )
	{
		m_state = move_back;
	}
	else if (length/*fabsf(m_transform.position.z) - fabsf(StartPos.z)*/ <= 0.01f && m_state == move_back)
	{
		m_state = move_flont;
	}

	switch (m_state){
	case move_none:
	{
		break;
	}
	case move_flont:
	{
		m_transform.position += m_dir * m_MoveSpeed.z;
		break;
	}
	case move_back:
	{
		m_transform.position -= m_dir * m_MoveSpeed.z;
		break;
	}
	}
	


	C3DImage::Update();

	if (IsHitPlayer(m_transform.position, 1.0f))
	{
		m_player->SetParent(this);
		m_pAudio->PlayCue("Lift",false);
	}
	else if (!IsHitPlayer(m_transform.position, 1.0f))
	{
		if (m_player->GetParent() == this){
			m_player->SetParent(nullptr);
		}
	}


}

void MoveFloor::Draw()
{
	SetUpTechnique();
	C3DImage::Draw();
}


void MoveFloor::Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos){
	//この引数に渡すのはボックスhalfsizeなので、0.5倍する。
	m_collisionShape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	groundTransform.setRotation(btQuaternion(m_transform.angle.x, m_transform.angle.y, m_transform.angle.z, m_transform.angle.w));
	float mass = 0.0f;

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	//m_rigidBody->setUserIndex(1);
	//ワールドに追加。
	SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->AddRigidBody(m_rigidBody);
}



bool MoveFloor::IsHitPlayer(D3DXVECTOR3 pos, float radius)
{
	m_WorldMatrix = GetWorldMatrix();
	D3DXMatrixInverse(&m_InvWorld, nullptr, &m_WorldMatrix);


	PlayerPos = m_player->GetPos();

	D3DXVec3Transform(&dimension, &PlayerPos, &m_InvWorld);

	if (fabsf(dimension.x) < 1.5f && fabsf(dimension.z) < 1.5f && dimension.y <= 1.7f && dimension.y >= 0.6f)
	{
		return true;
	}

	return false;
}
