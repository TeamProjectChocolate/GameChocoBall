#pragma once
#include "C3DImage.h"
#include "BulletPhysics.h"

#define MaxCollision 100

struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

class CField :
	public C3DImage
{
public:
	CField(){
		m_ghostObject = nullptr;
		m_myMotionState = nullptr;
		m_myMotionState = nullptr;
		strcpy(m_pFileName, "image/SUTE2.x" /*"image/stage2.x"*/);
	};
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
	btBoxShape*	m_groundShape[MaxCollision];	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody[MaxCollision];	//���́B
	btDefaultMotionState* m_myMotionState;
	
};

