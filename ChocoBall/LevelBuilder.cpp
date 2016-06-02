#include "stdafx.h"
#include "LevelBuilder.h"
#include "EnemyManager.h"
#include "Field.h"
#include "CollisionType.h"
#include <vector>
#include "CBManager.h"

enum GimmickType{
	GimmickType_Chocoball,
	GimmickType_Wall,
};
struct SEnemyAndGimmickInfo{
	D3DXVECTOR3 pos;
	D3DXQUATERNION rot;
	D3DXVECTOR3 scale;
	int enemyType;
	int gimmickType;
};
//ステージ切り替えで必要

// ステージ1
static SEnemyAndGimmickInfo infoTable[] = {
#include "EnemyGimmickInfo.h"
};


static SEnemyAndGimmickInfo* infoTableArray[] = {
	infoTable
};

static int InfoTableSizeArray[] = {
	ARRAYSIZE(infoTable)
};
//ステージ切り替えで必要

// ステージ1
static SCollisionInfo GimmickTriggerInfoTable[] = {
#include "GimmickTriggerInfo.h"
};


static SCollisionInfo* GimmickinfoTableArray[] = {
	GimmickTriggerInfoTable
};

static int GimmickInfoTableSizeArray[] = {
	ARRAYSIZE(GimmickTriggerInfoTable)
};


CLevelBuilder::CLevelBuilder()
{
	memset(m_ghostObject, 0, sizeof(m_ghostObject));//ghostobjectの配列を0からメモリ分初期化
	m_IsStage = STAGE_ID::STAGE_NONE;
}
CLevelBuilder::~CLevelBuilder()
{
	for (int i = 0; i < MaxCollision; i++){
		if (m_ghostObject[i]){
			g_bulletPhysics.RemoveCollisionObject(m_ghostObject[i]);
		}
	}
	for (auto cb : m_chocoballMgrList){
		delete cb;
	}
}
void CLevelBuilder::Build()
{
	int StageID = static_cast<int>(m_IsStage);
	int tableSize = InfoTableSizeArray[StageID];
	SEnemyAndGimmickInfo* pInfo = infoTableArray[StageID];
	for (int i = 0; i < tableSize; i++){
		const SEnemyAndGimmickInfo& info = pInfo[i];
		if (info.enemyType == 0){
			//敵を生成。
			extern CEnemyManager g_enemyMgr;
			CEnemy* enemy = new CEnemy;
			enemy->Initialize();
			//CEnemy* enemy = SINSTANCE(CObjectManager)->GenerationObject<CEnemy>(_T("Enemy"), PRIORTY::OBJECT3D, false);
			infoTable[i].pos.x = infoTable[i].pos.x * -1;
			infoTable[i].pos.z = infoTable[i].pos.z * -1;
			enemy->SetInitPosition(infoTable[i].pos);
			g_enemyMgr.AddEnemy(enemy);
		}
		if (info.gimmickType == GimmickType_Chocoball){
			//チョコボールを生成。
			CCBManager* mgr =new CCBManager;
			m_chocoballMgrList.push_back(mgr);
			D3DXVECTOR3 startPos(-infoTable[i].pos.x, infoTable[i].pos.y, -infoTable[i].pos.z);
			D3DXQUATERNION rot(infoTable[i].rot.x, infoTable[i].rot.y, infoTable[i].rot.z, infoTable[i].rot.w);
			D3DXMATRIX mRot;
			D3DXMatrixRotationQuaternion(&mRot, &rot);
			D3DXVECTOR3 back;
			back.x = -mRot.m[2][0];
			back.y = -mRot.m[2][1];
			back.z = -mRot.m[2][2];
			mgr->SetStartPosition(startPos);
			mgr->SetEndPosition(startPos + back);
		}
		if (info.gimmickType == GimmickType_Wall){
			//ギミックの生成
			CBuildBlock* buildBlock = SINSTANCE(CObjectManager)->GenerationObject<CBuildBlock>(_T("B_Block"), PRIORTY::OBJECT3D, false);
			buildBlock->Initialize(
				D3DXVECTOR3(-infoTable[i].pos.x, infoTable[i].pos.y, -infoTable[i].pos.z),
				infoTable[i].rot
			);

		}
	}
	//この引数に渡すのはボックスのhalfsizeなので、0.5倍する。
	int arraySize2 = GimmickInfoTableSizeArray[StageID];	//配列の要素数を返す。
	SCollisionInfo* pInfo2 = GimmickinfoTableArray[StageID];
	for (int i = 0; i < arraySize2; i++) {
		SCollisionInfo& collision = pInfo2[i];
		m_GhostShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(-collision.pos.x, collision.pos.y, -collision.pos.z));
		groundTransform.setRotation(btQuaternion(collision.rotation.x, collision.rotation.y, collision.rotation.z, collision.rotation.w));


		m_ghostObject[i] = new btGhostObject();
		m_ghostObject[i]->activate();
		m_ghostObject[i]->setCollisionShape(m_GhostShape[i]);
		m_ghostObject[i]->setWorldTransform(groundTransform);
		m_ghostObject[i]->setUserIndex(CollisionType_ChocoballTrigger);
		m_ghostObject[i]->setUserPointer(m_chocoballMgrList[i]);
		//ワールドに追加。
		g_bulletPhysics.AddCollisionObject(m_ghostObject[i]);
	}
}
