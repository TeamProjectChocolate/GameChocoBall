#pragma once
#include "Number.h"
#include "Bullet.h"

#define TIMEBONUS 10
#define ENEMY_BONUS 20

class CScoreCalc
{
public:
	CScoreCalc();
	~CScoreCalc();
	void kasan();
	void Update();
private:
	int score;
	CPlayer* m_player;
	CNumber* m_number;
};