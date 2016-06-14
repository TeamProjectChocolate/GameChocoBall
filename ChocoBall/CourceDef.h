#pragma once
#include "stdafx.h"
#include "Infomation.h"

typedef struct COURCE_BLOCK{
	D3DXVECTOR3 startPosition;
	D3DXVECTOR3 endPosition;
	int blockNo;
	COURCE_BLOCK* nextBlock;
};

class CCourceDef{
public:
	CCourceDef(){ m_courceNum = 0; };
	~CCourceDef(){};
	void Initialize();
	COURCE_BLOCK FindCource(D3DXVECTOR3);
	D3DXVECTOR3 EndCource(){
		return m_courceEnd;
	}
	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
private:
	COURCE_BLOCK m_cource;
	int m_courceNum;
	D3DXVECTOR3 m_courceEnd;
	STAGE_ID m_StageID;
};



// ステージ1のコース定義
static D3DXVECTOR3 CourceDefine_1[] = {
#include "CourceDefStage1.h"
};
static D3DXVECTOR3 CourceDefine_2[] = {
#include "CourceDefStage2.h"
};
static D3DXVECTOR3 CourceDefine_3[] = {
#include "CourceDefStage3.h"
};

static D3DXVECTOR3* CourceDefineArray[] = {
	CourceDefine_1,
	CourceDefine_2,
	CourceDefine_3
};

static int CourceDefineNumArray[] = {
	ARRAYSIZE(CourceDefine_1),
	ARRAYSIZE(CourceDefine_2),
	ARRAYSIZE(CourceDefine_3)
};