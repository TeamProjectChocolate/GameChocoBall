#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "DirectInput.h"
#include "BulletPhysics.h"

class CEnemy : public C3DImage
{
public:
	CEnemy(){
		m_pInput = nullptr;
		m_ghostObject = nullptr;
		m_collisionShape = nullptr;
		m_rigidBody = nullptr;
		m_myMotionState = nullptr;
		strcpy(m_pFileName, "image/kyu.x");
	};
	~CEnemy();

	void Initialize()override;
	void Update()override;
	void Draw()override;
	D3DXVECTOR3 GetPos(){
		return m_transform.position;
	}
private:
	CDirectInput* m_pInput;

	//��������BulletPhysics�ŏՓ˔�����s�����߂̃����o�ϐ��B
	btGhostObject*		m_ghostObject;		//!<�S�[�X�g�B���̂̕ς��ɂȂ���́B���S�ɕ��������ɔC���������͍̂��̂��g���B
	btSphereShape*		m_collisionShape;	//!<�R���W�����`��B
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
	D3DXVECTOR3		m_position;
	float			m_radius;
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x�B
	float			g_currentAngleY;	//���݂̕���
	float			g_targetAngleY;		//������������
	float			g_turnSpeed;		//��]���x
	bool			isTurn;				//��]�t���O
};

