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
static SEnemyAndGimmickInfo infoTable[] = {
#include "EnemyGimmickInfo.h"
};
SCollisionInfo GimmickTriggerInfoTable[] = {
#include "GimmickTriggerInfo.h"
};

CLevelBuilder::CLevelBuilder()
{
	memset(m_ghostObject, 0, sizeof(m_ghostObject));//ghostobjectの配列を0からメモリ分初期化
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
	int tableSize = ARRAYSIZE(infoTable);
	for (int i = 0; i < tableSize; i++){
		const SEnemyAndGimmickInfo& info = infoTable[i];
		//if (info.enemyType == 0){
		//	//敵を生成。
		//	extern CEnemyManager g_enemyMgr;
		//	CEnemyLR* enemylr = new CEnemyLR;
		//	//CEnemyLR* enemy = SINSTANCE(CObjectManager)->GenerationObject<CEnemy>(_T("Enemy"), PRIORTY::OBJECT3D, false);
		//	infoTable[i].pos.x = infoTable[i].pos.x * -1;
		//	infoTable[i].pos.z = infoTable[i].pos.z * -1;
		//	enemylr->SetInitPosition(infoTable[i].pos);
		//	g_enemyMgr.AddEnemy(enemylr);
		//}
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
		if (info.enemyType == 0){
			//敵を生成。
			extern CEnemyManager g_enemyMgr;
			CEnemyjamp* enemyjamp = new CEnemyjamp;
			//CEnemy* enemy = SINSTANCE(CObjectManager)->GenerationObject<CEnemy>(_T("Enemy"), PRIORTY::OBJECT3D, false);
			infoTable[i].pos.x = infoTable[i].pos.x * -1;
			infoTable[i].pos.z = infoTable[i].pos.z * -1;
			enemyjamp->SetInitPosition(infoTable[i].pos);
			g_enemyMgr.AddEnemy(enemyjamp);
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
	int arraySize2 = ARRAYSIZE(GimmickTriggerInfoTable);	//配列の要素数を返す。
	for (int i = 0; i < arraySize2; i++) {
		SCollisionInfo& collision = GimmickTriggerInfoTable[i];
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
