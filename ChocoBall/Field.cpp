#include "stdafx.h"
#include "Field.h"
#include "BulletPhysics.h"



CField::~CField()
{
}

void CField::Initialize(){

	SCollisionInfo collisionInfoTable[] = {
		{
			//�n�ʂ̃R���W����
			D3DXVECTOR3(0.0f, -2.0f, 0.0f),		//���W�B
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//��]�B
			D3DXVECTOR3(4.0f, 0.6f, 20.0f),	//�g��B	
		},
		{
			//���ǂ̃R���W�����B
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//���W�B
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//��]�B
			D3DXVECTOR3(1.0f, 1.0f, 1.0f),		//�g��B	
		},
		{
			//�E�ǂ̃R���W�����B
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//���W�B
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//��]�B
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//�g��B	
		}
	};

	C3DImage::Initialize();
	m_transform.position = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXToRadian(90.0f));
	//m_transform.angle = D3DXVECTOR3(2.5f, 1.65f, 2.48f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetAlive(true);


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
			m_rigidBody[i]->activate();

			//���[���h�ɒǉ��B
			g_bulletPhysics.AddRigidBody(m_rigidBody[i]);
		}
	}
	C3DImage::SetImage();
}

void CField::Update(){
	C3DImage::Update();
}

void CField::Draw(){
	SetUpTechnique();
	C3DImage::Draw();
}