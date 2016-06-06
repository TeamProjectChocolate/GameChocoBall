#include "stdafx.h"
#include "LevelBuilder.h"
#include "EnemyManager.h"
#include "Field.h"
#include "CollisionType.h"
#include <vector>
#include "CBManager.h"
#include "EnemyLR.h"
#include "StageTable.h"


CLevelBuilder::CLevelBuilder()
{
	memset(m_ghostObject, 0, sizeof(m_ghostObject));//ghostobjectの配列を0からメモリ分初期化
	m_IsStage = STAGE_ID::STAGE_NONE;
}

CLevelBuilder::~CLevelBuilder()
{
	CObjectManager* objMgr = SINSTANCE(CObjectManager);
	for (int i = 0; i < MaxCollision; i++){
		if (m_ghostObject[i]){
			objMgr->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->RemoveCollisionObject(m_ghostObject[i]);
		}
	}
	for (auto cb : m_chocoballMgrList){
		objMgr->DeleteGameObjectImmediate(cb);
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
			CEnemyLR* enemy = new CEnemyLR;
			enemy->Initialize();
			//CEnemy* enemy = SINSTANCE(CObjectManager)->GenerationObject<CEnemy>(_T("Enemy"), PRIORTY::OBJECT3D, false);
			pInfo[i].pos.x = pInfo[i].pos.x * -1;
			pInfo[i].pos.z = pInfo[i].pos.z * -1;
			enemy->SetInitPosition(pInfo[i].pos);
			g_enemyMgr.AddEnemy(enemy);
		}
		//else if (info.enemyType == 1){
		//	//敵を生成。
		//	extern CEnemyManager g_enemyMgr;
		//	CEnemyFB* enemyfb = new CEnemyFB;
		//	//CEnemy* enemy = SINSTANCE(CObjectManager)->GenerationObject<CEnemy>(_T("Enemy"), PRIORTY::OBJECT3D, false);
		//	infoTable[i].pos.x = infoTable[i].pos.x * -1;
		//	infoTable[i].pos.z = infoTable[i].pos.z * -1;
		//	enemyfb->SetInitPosition(infoTable[i].pos);
		//	g_enemyMgr.AddEnemy(enemyfb);
		//}
		//else if (info.enemyType == 2){
		//	//敵を生成。
		//	extern CEnemyManager g_enemyMgr;
		//	CEnemyjamp* enemyjamp = new CEnemyjamp;
		//	//CEnemy* enemy = SINSTANCE(CObjectManager)->GenerationObject<CEnemy>(_T("Enemy"), PRIORTY::OBJECT3D, false);
		//	infoTable[i].pos.x = infoTable[i].pos.x * -1;
		//	infoTable[i].pos.z = infoTable[i].pos.z * -1;
		//	enemyjamp->SetInitPosition(infoTable[i].pos);
		//	g_enemyMgr.AddEnemy(enemyjamp);
		//}

		if (info.gimmickType == GimmickType_Chocoball){
			//チョコボールを生成。
			CCBManager* mgr =new CCBManager;
			m_chocoballMgrList.push_back(mgr);
			D3DXVECTOR3 startPos(-pInfo[i].pos.x, pInfo[i].pos.y, -pInfo[i].pos.z);
			D3DXQUATERNION rot(pInfo[i].rot.x, pInfo[i].rot.y, pInfo[i].rot.z, pInfo[i].rot.w);
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
				D3DXVECTOR3(-pInfo[i].pos.x, pInfo[i].pos.y, -pInfo[i].pos.z),
				pInfo[i].rot
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
		SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->AddCollisionObject(m_ghostObject[i]);
	}
}
