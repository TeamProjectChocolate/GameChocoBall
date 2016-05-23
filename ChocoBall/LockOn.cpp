#include "stdafx.h"
#include "LockOn.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "ObjectManager.h"

LockOn::LockOn()
{
}

LockOn::~LockOn()
{
}

float LockOn::LockOnRotation(float _X, D3DXVECTOR3 position, int lockonEnemyIndex)
{
	static float fHALF_PI = fPI / 2.0f;
	CEnemyManager* EnemyManager = (SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager")));
	CEnemy* Enemy = EnemyManager->GetEnemy(lockonEnemyIndex);
	D3DXVECTOR3 dist;
	dist = Enemy->GetPos() - position;
	//�G����O�̎��̉�]�p�x�̌v�Z
	_X = fabsf(atan(dist.z / dist.x));
	if (dist.x >= 0.0f){
		if (dist.z >= 0.0f){
			_X = -fHALF_PI - _X;
		}
		else{
			_X = -fHALF_PI + _X;
		}
	}
	else if (dist.x < 0.0f){
		if (dist.z >= 0.0f){
			_X = fHALF_PI + _X;
		}
		else{
			_X = fHALF_PI - _X;
		}
	}
	return _X;
}

int LockOn::FindNearEnemy(D3DXVECTOR3 position)
{
	float Min;

	CEnemyManager* EnemyManager = (SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager")));
	CEnemy* Enemy;
	Min = 99999;	//�ԕ�
	//�G20�̕��̋����̎擾
	for (int K = 0; K < 20; K++)
	{
		Enemy = EnemyManager->GetEnemy(K);
		D3DXVECTOR3 dist;
		//�v���C���[�ƓG�̋����v�Z
		dist = Enemy->GetPos() - position;
		float len = D3DXVec3Length(&dist);
		
		if (len < Min)
		{
			//��ԋ߂��G���m��
			m_lockonEnemyIndex = K;
			Min = len;//��ԒZ������
		}
	}

	return m_lockonEnemyIndex;
}