#pragma once
#include "C3DImage.h"
#include "BulletPhysics.h"

#define MaxCollision 100

class CField :
	public C3DImage
{
public:
	CField(){
		m_ghostObject = nullptr;
		m_myMotionState = nullptr;
		strcpy(m_pFileName, "image/stage.x" /*"image/stage2.x"*/);
	};
	~CField();

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("ShadowTec");
	}
	void CreateCollision(){};
private:
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btGhostObject*		m_ghostObject;		//!<�S�[�X�g�B���̂̕ς��ɂȂ���́B���S�ɕ��������ɔC���������͍̂��̂��g���B
	btCollisionShape*	m_groundShape[MaxCollision];	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody[MaxCollision];	//���́B
	btDefaultMotionState* m_myMotionState;
};

