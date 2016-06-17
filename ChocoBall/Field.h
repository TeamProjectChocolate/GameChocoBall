#pragma once
#include "C3DImage.h"
#include "BulletPhysics.h"

#define MaxCollision 200


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
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btBoxShape*	m_groundShape[MaxCollision];	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody[MaxCollision];	//剛体。
	btDefaultMotionState* m_myMotionState;
	STAGE_ID m_StageID;
};

