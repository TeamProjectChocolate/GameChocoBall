#include "stdafx.h"
#include "Score.h"


CScoreCalc::CScoreCalc()
{
}

CScoreCalc::~CScoreCalc()
{

}
void CScoreCalc::Draw()
{
	if (true)//敵を倒した時のポイント加算
	{
		m_enemycounter++;
	}
	 m_timecounter += m_enemycounter * ENEMY_BONUS;
}