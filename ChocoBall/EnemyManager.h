#pragma once
#include "Enemy.h"
#include "EnemyLR.h"
#include "EnemyFB.h"
#include "Enemyjamp.h"
#include "GameObject.h"

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
			SAFE_DELETE(Enemy[enemyIndex]);
			Enemy[enemyIndex] = nullptr;
		}
		for (int i = enemyIndex; i < numEnemy - 1; i++){
			Enemy[i] = Enemy[i + 1];
		}
		numEnemy--;
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
};
