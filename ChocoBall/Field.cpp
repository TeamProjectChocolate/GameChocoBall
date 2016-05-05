#include "stdafx.h"
#include "Field.h"
#include "BulletPhysics.h"


CField::CField()
{
	strcpy(m_pFileName, "image/stage2.x");
}


CField::~CField()
{
}

void CField::Initialize(){
	C3DImage::Initialize();
	m_transform.position = D3DXVECTOR3(0.0f,0.6f, -16.5f);
	SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(90.0f));
	//m_transform.angle = D3DXVECTOR3(2.5f, 1.65f, 2.48f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetAlive(true);

	D3DXVECTOR3 boxSize(1000.0f, 11.5f, 1000.0f);
	D3DXVECTOR3 boxPosition(m_transform.position.x, m_transform.position.y-5.6f, m_transform.position.z);

	//剛体を初期化。
	{
		//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
		m_groundShape = new btBoxShape(btVector3(boxSize.x*0.5f, boxSize.y*0.5f, boxSize.z*0.5f));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(boxPosition.x, boxPosition.y, boxPosition.z));
		float mass = 0.0f;

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		m_myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape, btVector3(0, 0, 0));
		m_rigidBody = new btRigidBody(rbInfo);

		//ワールドに追加。
		g_bulletPhysics.AddRigidBody(m_rigidBody);

	}
	//m_rigidBody = new btRigidBody
	/*m_box.Create(boxSize, 0x88888888, true);
	m_box.SetPosition(boxPosition);
	m_box.UpdateWorldMatrix();
	m_light.SetDiffuseLightColor(0, CVector4(0.5f, 0.5f, 0.5f, 1.0f));
	m_light.SetDiffuseLightDirection(0, CVector3(0.0f, -1.0f, 0.0f));*/
	C3DImage::SetImage();
}

void CField::Update(){
	C3DImage::Update();
}

void CField::Draw(){
	SetUpTechnique();
	C3DImage::Draw();
}