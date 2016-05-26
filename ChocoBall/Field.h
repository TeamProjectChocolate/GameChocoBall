#pragma once
#include "C3DImage.h"
#include "BulletPhysics.h"

#define MaxCollision 100

struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 scale;
};

//�R���W�����̎��
enum CollisionType{

};
class CField :
	public C3DImage
{
public:
	CField(){
		memset(m_ghostObject, 0, sizeof(m_ghostObject));//ghostobject�̔z���0���烁������������
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
	btGhostObject*		m_ghostObject[MaxCollision];		//!<�S�[�X�g�B���̂̕ς��ɂȂ���́B���S�ɕ��������ɔC���������͍̂��̂��g���B
	btBoxShape*	m_groundShape[MaxCollision];	//�n�ʂ̃R���W�����`��B
	btBoxShape*	m_GhostShape[MaxCollision];	//�����蔻�肾��������R���W�����`��B
	btRigidBody*		m_rigidBody[MaxCollision];	//���́B
	btDefaultMotionState* m_myMotionState;
	
};

