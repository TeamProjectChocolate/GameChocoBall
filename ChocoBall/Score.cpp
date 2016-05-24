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
	if (true)//“G‚ð“|‚µ‚½Žž‚Ìƒ|ƒCƒ“ƒg‰ÁŽZ
	{
		m_enemycounter++;
	}
	 m_timecounter += m_enemycounter * ENEMY_BONUS;
}