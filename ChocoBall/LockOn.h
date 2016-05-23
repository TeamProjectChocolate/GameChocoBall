#pragma once
#include "stdafx.h"


class LockOn
{
public:
	LockOn();
	~LockOn();
	float LockOnRotation(float _X, D3DXVECTOR3 position, int lockonEnemyIndex);
	int FindNearEnemy(D3DXVECTOR3 position);
private:
	bool            LockOnflag;			//ロックオンフラグ
	int				m_lockonEnemyIndex;	//ロックオンしている敵のインデックス。
};
