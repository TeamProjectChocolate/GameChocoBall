#pragma once
#include "GameObject.h"

class CTurn
{
public:
	CTurn()
	{
		D3DXToRadian(10.0f);
	};
	~CTurn();
	//‰ñ“]ˆ—‚Ì‰Šú‰»
	void CTurn::Initialize();		
	//‰ñ“]ˆ—‚ÌXV
	void CTurn::Update(bool isTurn, float currentAngleY);	
	float Getm_currentAngleY()
	{
		return m_currentAngleY;
		
	}
private:
	float	m_currentAngleY;	//Œ»İ‚Ì•ûŒü
	float	m_targetAngleY;		//Œü‚«‚½‚¢•ûŒü
	float	m_turnSpeed;		//‰ñ“]‘¬“x
	float   m_cTurnSpeed;
	bool	isTurn;				//‰ñ“]ƒtƒ‰ƒO
};