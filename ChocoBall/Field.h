#pragma once
#include "C3DImage.h"
#include "BulletPhysics.h"


class CField :
	public C3DImage
{
public:
	CField(){
		m_myMotionState = nullptr;
		m_myMotionState = nullptr;
	};
	~CField();

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("ShadowTec");
	}
	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
	
private:
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	vector<btBoxShape*>	m_groundShape;	//�n�ʂ̃R���W�����`��B
	vector<btRigidBody*>		m_rigidBody;	//���́B
	btDefaultMotionState* m_myMotionState;
	STAGE_ID m_StageID;
};

