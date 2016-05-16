#include "C3DImage.h"

class Enemymanage
{
public:
	Enemymanage()
	{
		numEnemy = 0;
	}
	//敵の追加
	void AddEnemy(C3DImage* enemy)
	{
		Enemy[numEnemy] = enemy;
		numEnemy++;
	}

	int GetNumEnemy()
	{
		return numEnemy;	//エネミーの数を返す
	}
	//敵の配列の要素数をk返す
	C3DImage* GetEnemyArray()
	{
		return Enemy[20];
	}
private:
	int		numEnemy;	//敵の数。
	C3DImage* Enemy[20];
};

extern Enemymanage g_enemyMgr;	//敵の変数。
