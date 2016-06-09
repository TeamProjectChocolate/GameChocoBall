#pragma once 
#include "stdafx.h"
#include "C3DImage.h"

class EnemyBase : public C3DImage
{
public:
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("NotNormalMapNonAnimationFresnelTec");
	}
	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
protected:
	STAGE_ID m_StageID;
};