#include "stdafx.h"
#include "Field.h"
#include "BulletPhysics.h"

struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

SCollisionInfo collisionInfoTable[] = {
	{
		//�n�ʂ̃R���W����
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//���W�B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	//��]�B
		D3DXVECTOR3(20.0f, 0.6f, 20.0f),	//�g��B	
	},
	{
		//saka00�̃R���W�����B
		D3DXVECTOR3(3.0f, 3.0f,3.0f),		//���W�B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//��]�B
		D3DXVECTOR3(20.0f, 0.6f, 20.0f),	//�g��B	
	},
	{
		//saka01�̃R���W�����B
		D3DXVECTOR3(10.0f, 10.0f, 10.0f),			//���W�B
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//��]�B
		D3DXVECTOR3(100.0f, 200.0f, 100.0f),	//�g��B	
	},
};
CField::~CField()
{
}

void CField::Initialize(){
	C3DImage::Initialize();
	m_transform.position = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(90.0f));
	//m_transform.angle = D3DXVECTOR3(2.5f, 1.65f, 2.48f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetAlive(true);

	//D3DXVECTOR3 boxSize(5.0f, 11.5f, 5.0f);
	//D3DXVECTOR3 boxPosition(m_transform.position.x, m_transform.position.y - 5.6f, m_transform.position.z);

	//���̂��������B
	{
		//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
		int arraySize = ARRAYSIZE(collisionInfoTable);	//�z��̗v�f����Ԃ��B
		for (int i = 0; i < arraySize; i++) {
			SCollisionInfo& collision = collisionInfoTable[i];
			m_groundShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(collision.pos.x, collision.pos.y, collision.pos.z));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			m_myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape[i], btVector3(0, 0, 0));
			m_rigidBody[i] = new btRigidBody(rbInfo);

			//���[���h�ɒǉ��B
			g_bulletPhysics.AddRigidBody(m_rigidBody[i]);
		}
	}
	C3DImage::SetImage();
}


//void CreateCollision()
//{
//	int arraySize = ARRAYSIZE(collisionInfoTable);
//	for (int i = 0; i < arraySize; i++) {
//		SCollisionInfo& collision = collisionInfoTable[i];
//		//�����ō��̂Ƃ���o�^����B
//	}
//}

void CField::Update(){
	C3DImage::Update();
}

void CField::Draw(){
	SetUpTechnique();
	C3DImage::Draw();
}