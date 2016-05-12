#pragma once
#include "GameObject.h"

class CTurn : public CGameObject
{
public:
	CTurn();
	~CTurn();

private:
	float			g_currentAngleY;	//Œ»İ‚Ì•ûŒü
	float			g_targetAngleY;		//Œü‚«‚½‚¢•ûŒü
	float			g_turnSpeed;		//‰ñ“]‘¬“x
	bool			isTurn;				//‰ñ“]ƒtƒ‰ƒO
};