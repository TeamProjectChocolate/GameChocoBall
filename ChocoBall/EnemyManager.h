#pragma once
#include "Enemy.h"
//#include "Enemy2.h"
#include "GameObject.h"


class CEnemyManager:public CGameObject
{
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	CEnemyManager()
	{
		numEnemy = 0;
	}
	void AddEnemy(EnemyBase* enemy)
	{
		Enemy[numEnemy] = enemy;
		numEnemy++;
	}
	void DeleteEnemy(EnemyBase* enemy)
	{
		Enemy[numEnemy] = enemy;
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
private:
	int		numEnemy;	//敵の数。
	EnemyBase* Enemy[20];
};

//extern CEnemyManager g_enemyMgr;	//敵の変数。
