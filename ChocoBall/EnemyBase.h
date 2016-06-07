#pragma once 
#include "stdafx.h"
#include "C3DImage.h"

class EnemyBase : public C3DImage
{
public:
	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
protected:
	STAGE_ID m_StageID;
};