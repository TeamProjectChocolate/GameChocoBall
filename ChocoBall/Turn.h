#pragma once
#include "GameObject.h"

class CTurn : public CGameObject
{
public:
	CTurn();
	~CTurn();

private:
	float			g_currentAngleY;	//現在の方向
	float			g_targetAngleY;		//向きたい方向
	float			g_turnSpeed;		//回転速度
	bool			isTurn;				//回転フラグ
};