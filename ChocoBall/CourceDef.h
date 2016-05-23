#pragma once
#include "stdafx.h"

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
private:
	COURCE_BLOCK m_cource;
	int m_courceNum;
	D3DXVECTOR3 m_courceEnd;
};