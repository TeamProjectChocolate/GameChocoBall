#pragma once
#include "Enemy.h"
#include "EnemyLR.h"
#include "EnemyFB.h"
#include "Enemyjamp.h"
#include "GameObject.h"
#include "ShadowRender.h"

class CEnemyManager:public CGameObject
{
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void DeleteAll();
	CEnemyManager()
	{
		numEnemy = 0;
	}
	~CEnemyManager(){
		this->DeleteAll();
	}

	void AddEnemy(EnemyBase* enemy)
	{
		Enemy[numEnemy] = enemy;
		numEnemy++;
	}
	void DeleteEnemy(EnemyBase* enemy)
	{
		enemy->OnDestroy();
		int enemyIndex = -1;
		for (int i = 0; i < numEnemy; i++){
			if (enemy == Enemy[i]){
				enemyIndex = i;
				break;
			}
		}
		if (enemyIndex == -1){
			return;
		}
		else{
			m_DeleteObjects.push_back(Enemy[enemyIndex]);
			SINSTANCE(CShadowRender)->DeleteObject(Enemy[enemyIndex]);
		}
		for (int i = enemyIndex; i < numEnemy - 1; i++){
			Enemy[i] = Enemy[i + 1];
		}
	}

	void ExcuteDeleteObjects(){
		int size = m_DeleteObjects.size();
		for (int idx = 0; idx < size;idx++){
			SAFE_DELETE(m_DeleteObjects[idx]);
			m_DeleteObjects[idx] = nullptr;
			numEnemy--;
		}
		m_DeleteObjects.clear();
	}

	int GetNumEnemy()
	{
		return numEnemy;	//エネミーの数を返す
	}
	EnemyBase* GetEnemy(short num){
		return Enemy[num];
	}

	EnemyBase* GetEnemyArray()
	{
		return Enemy[20];
	}

	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
private:
	int		numEnemy;	//敵の数。
	EnemyBase* Enemy[20];
	STAGE_ID m_StageID;
	vector<EnemyBase*> m_DeleteObjects;
};
