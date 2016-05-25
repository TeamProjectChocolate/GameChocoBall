#include "stdafx.h"
#include "LevelBuilder.h"
#include "EnemyManager.h"

struct SEnemyAndGimmickInfo{
	D3DXVECTOR3 pos;
	D3DXQUATERNION rot;
	D3DXVECTOR3 scale;
	int enemyType;
	int gimmickType;
};
static SEnemyAndGimmickInfo infoTable[] = {
#include "EnemyGimmickInfo.h"
};

CLevelBuilder::CLevelBuilder()
{

}
CLevelBuilder::~CLevelBuilder()
{

}
void CLevelBuilder::Build()
{
	int tableSize = ARRAYSIZE(infoTable);
	for (int i = 0; i < tableSize; i++){
		const SEnemyAndGimmickInfo& info = infoTable[i];
		if (info.enemyType == 0){
			//敵を生成。
			extern CEnemyManager g_enemyMgr;
			CEnemy* enemy = new CEnemy;
			//CEnemy* enemy = SINSTANCE(CObjectManager)->GenerationObject<CEnemy>(_T("Enemy"), PRIORTY::OBJECT3D, false);
			infoTable[i].pos.x = infoTable[i].pos.x * -1;
			infoTable[i].pos.z = infoTable[i].pos.z * -1;
			enemy->SetInitPosition(infoTable[i].pos);
			g_enemyMgr.AddEnemy(enemy);
		}
		if (info.gimmickType == 0){
			//壁ギミックを生成。
		}
	}
}
