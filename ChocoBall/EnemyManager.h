#include "C3DImage.h"

class Enemymanage
{
public:
	Enemymanage()
	{
		numEnemy = 0;
	}
	//�G�̒ǉ�
	void AddEnemy(C3DImage* enemy)
	{
		Enemy[numEnemy] = enemy;
		numEnemy++;
	}

	int GetNumEnemy()
	{
		return numEnemy;
	}
	//�G�̔z��̗v�f����k�Ԃ�
	C3DImage* GetEnemyArray()
	{
		return Enemy[20];
	}
private:
	int		numEnemy;	//�G�̐��B
	C3DImage* Enemy[20];
};

extern Enemymanage g_enemyMgr;	//�G�̕ϐ��B
