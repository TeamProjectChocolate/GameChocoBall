#pragma once
#include "GameObject.h"

class CTurn : public CGameObject
{
public:
	CTurn();
	~CTurn();

private:
	float			g_currentAngleY;	//���݂̕���
	float			g_targetAngleY;		//������������
	float			g_turnSpeed;		//��]���x
	bool			isTurn;				//��]�t���O
};