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
	if (true)//�G��|�������̃|�C���g���Z
	{
		m_enemycounter++;
	}
	 m_timecounter += m_enemycounter * ENEMY_BONUS;
}