#pragma once
#include "Number.h"

#define TIMEBONUS 10
#define ENEMY_BONUS 20

class CScoreCalc
{
public:
	CScoreCalc();
	~CScoreCalc();
	void SetTimeCounter(int time)
	{
		m_timecounter = time;
	}
	void SetEnemyCounter(int enemy)
	{
		m_enemycounter = enemy;
	}

private:
	int m_enemycounter = 0;
	int m_timecounter = 0;
	
};