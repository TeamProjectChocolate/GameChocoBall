#pragma once
#include "stdafx.h"


class CLockOn
{
public:
	CLockOn();
	~CLockOn();
	float LockOnRotation(float _X, D3DXVECTOR3 position, int lockonEnemyIndex);
	int FindNearEnemy(D3DXVECTOR3 position);
	float LockOnRotation2(float _X, D3DXVECTOR3 position, int lockonBlockIndex);
	int FindNearBlock(D3DXVECTOR3 position);
private:
	bool LockOnflag;		//���b�N�I���t���O
	int	m_lockonEnemyIndex;	//���b�N�I�����Ă���G�̃C���f�b�N�X�B
	int m_lockonBlock;		//���b�N�I�����Ă���u���b�N�̃C���f�b�N�X
};
