#pragma once
#include"stdafx.h"
#include "GameObject.h"

class CTurn
{
public:
	CTurn()
	{
		D3DXToRadian(10.0f);
	};
	~CTurn();
	//��]�����̏�����
	void CTurn::Initialize();		
	//��]�����̍X�V
	float CTurn::Update(bool isTurn, float currentAngleY);

	float Getm_currentAngleY()
	{
		return m_currentAngleY;
		
	}

private:
	float	m_currentAngleY;	//���݂̕���
	float	m_targetAngleY;		//������������
	float	m_turnSpeed;		//��]���x
	float   m_cTurnSpeed;
	bool	isTurn;				//��]�t���O
	bool    LockOnflag;			//���b�N�I���t���O
};