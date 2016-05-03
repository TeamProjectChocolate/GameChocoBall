#pragma once
#include "C3DImage.h"
#include "BulletPhysics.h"

class CField :
	public C3DImage
{
public:
	CField();
	~CField();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("ShadowTec");
	}
private:
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btGhostObject*		m_ghostObject;		//!<�S�[�X�g�B���̂̕ς��ɂȂ���́B���S�ɕ��������ɔC���������͍̂��̂��g���B
	btCollisionShape*	m_groundShape;	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody;	//���́B
	btDefaultMotionState* m_myMotionState;
};

