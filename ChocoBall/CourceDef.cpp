#include "stdafx.h"
#include "CourceDef.h"

void CCourceDef::Initialize(){
	static D3DXVECTOR3 courcepos[] = {
		#include "Cource.h"
	};

	int arraySize = ARRAYSIZE(courcepos);
	COURCE_BLOCK* itr = &m_cource;
	for(int num = 0; num + 1 < arraySize; num++){
		itr->startPosition = courcepos[num];
		itr->endPosition = courcepos[num + 1];
		itr->startPosition.x *= -1.0f;
		itr->startPosition.z *= -1.0f;
		itr->endPosition.x *= -1.0f;
		itr->endPosition.z *= -1.0f;
		itr->blockNo = num;
		COURCE_BLOCK* node = new COURCE_BLOCK;
		itr->nextBlock = node;
		m_courceNum++;
		if (num + 2 >= arraySize){
			itr->nextBlock = nullptr;
		}
		else{
			itr = node;
		}
	}
}

COURCE_BLOCK CCourceDef::FindCource(D3DXVECTOR3 pos){
	COURCE_BLOCK* itr = &m_cource;
	for (int num = 0; num < m_courceNum; num++){
		D3DXVECTOR3 endvector = itr->endPosition - itr->startPosition;
		D3DXVECTOR3 Playervector = pos - itr->startPosition;
		D3DXVECTOR3 Dir;
		float Distance = D3DXVec3Length(&endvector);
		D3DXVec3Normalize(&Dir, &endvector);
		 
		float PlayerDist = D3DXVec3Dot(&Dir, &Playervector);
		if (PlayerDist <= Distance){
			return *itr;
		}
		itr = itr->nextBlock;
	}
}
