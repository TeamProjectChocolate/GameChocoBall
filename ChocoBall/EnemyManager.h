#pragma once
#include "Enemy.h"
#include "GameObject.h"

#define ENEMYNUM 1

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
	void AddEnemy(CEnemy* enemy)
	{
		Enemy[numEnemy] = enemy;
		numEnemy++;
	}
	void DeleteEnemy(CEnemy* enemy)
	{
		Enemy[numEnemy] = enemy;
		numEnemy--;
	}

	int GetNumEnemy()
	{
		return numEnemy;	//�G�l�~�[�̐���Ԃ�
	}

	CEnemy* GetEnemy(short num){
		return Enemy[num];
	}

	CEnemy* GetEnemyArray()
	{
		return Enemy[20];
	}
private:
	int		numEnemy;	//�G�̐��B
	CEnemy* Enemy[20];
};

//extern CEnemyManager g_enemyMgr;	//�G�̕ϐ��B
