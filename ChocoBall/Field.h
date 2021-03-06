#pragma once
#include "C3DImage.h"
#include "BulletPhysics.h"
#include "StageTable.h"

class CZBufferSphere;

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
	void DrawDepth(LPD3DXEFFECT, const D3DXVECTOR2&)override;
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("ShadowMaskTec");
	}
	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
	
private:
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	vector<btBoxShape*>	m_groundShape;	//地面のコリジョン形状。
	vector<btRigidBody*>		m_rigidBody;	//剛体。
	btDefaultMotionState* m_myMotionState;
	STAGE_ID m_StageID;
	CZBufferSphere* m_czbuffersphere;
};

