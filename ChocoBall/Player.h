#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "DirectInput.h"
#include "BulletPhysics.h"



class CPlayer : public C3DImage
{
public:
	CPlayer();
	~CPlayer();
	void Initialize()override;
	void Initialize(float,float);
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
	D3DXVECTOR3 m_position;
	float			m_radius;
	D3DXVECTOR3		m_moveSpeed;	//�ړ����x�B
	
};

namespace tkEngine{
	const D3DXVECTOR3 vec3Zero = { 0.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3Right = { 1.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3Left = { -1.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3Up = { 0.0f, 1.0f, 0.0f };
	const D3DXVECTOR3 vec3Down = { 0.0f, -1.0f, 0.0f };
	const D3DXVECTOR3 vec3Front = { 0.0f, 0.0f, 1.0f };
	const D3DXVECTOR3 vec3Back = { 0.0f, 0.0f, -1.0f };

	const D3DXVECTOR3 vec3AxisX = { 1.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3AxisY = { 0.0f, 1.0f, 0.0f };
	const D3DXVECTOR3 vec3AxisZ = { 0.0f, 0.0f, 1.0f };
}