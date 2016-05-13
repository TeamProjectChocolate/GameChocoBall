#include "C3DImage.h"

class Enemymanage
{
public:
	Enemymanage()
	{
		numEnemy = 0;
	}
	void AddEnemy(C3DImage* enemy)
	{
		Enemy[numEnemy] = enemy;
		numEnemy++;
	}
	int GetNumEnemy()
	{
		return numEnemy;
	}
	C3DImage* GetEnemyArray()
	{
		return Enemy[20];
	}
private:
	int		numEnemy;	//“G‚Ì”B
	C3DImage* Enemy[20];
};

extern Enemymanage g_enemyMgr;	//“G‚Ì•Ï”B
