#include "stdafx.h"
#include "LockOn.h"
#include "EnemyBase.h"
#include "EnemyManager.h"
#include "ObjectManager.h"

CLockOn::CLockOn()
{
}

CLockOn::~CLockOn()
{
}

float CLockOn::LockOnRotation(float _X, D3DXVECTOR3 position, int lockonEnemyIndex)
{
	static float fHALF_PI = fPI / 2.0f;
	CEnemyManager* EnemyManager = (SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager")));
	EnemyBase* Enemy = EnemyManager->GetEnemy(lockonEnemyIndex);
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

int CLockOn::FindNearEnemy(D3DXVECTOR3 position)
{
	float Min;

	CEnemyManager* EnemyManager = (SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager")));
	EnemyBase* Enemy = nullptr;
	m_lockonEnemyIndex = -1;
	int NumEnemy = EnemyManager->GetNumEnemy();
	Min = 99999;	//�ԕ�
	//�G20�̕��̋����̎擾
	for (int K = 0; K < NumEnemy; K++)
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

//float CLockOn::LockOnRotation2(float _X, D3DXVECTOR3 position, int lockonBlockIndexW, int lockonBlockIndexH)
//{
//
//	static float fHALF_PI = fPI / 2.0f;
//	CEnemyManager* EnemyManager = (SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager")));
//	CEnemy* Enemy = EnemyManager->GetEnemy(lockonEnemyIndex);
//	D3DXVECTOR3 dist;
//	dist = Enemy->GetPos() - position;
//	//�G����O�̎��̉�]�p�x�̌v�Z
//	_X = fabsf(atan(dist.z / dist.x));
//	if (dist.x >= 0.0f){
//		if (dist.z >= 0.0f){
//			_X = -fHALF_PI - _X;
//		}
//		else{
//			_X = -fHALF_PI + _X;
//		}
//	}
//	else if (dist.x < 0.0f){
//		if (dist.z >= 0.0f){
//			_X = fHALF_PI + _X;
//		}
//		else{
//			_X = fHALF_PI - _X;
//		}
//	}
//	return _X;
//}
//
//int CLockOn::FindNearBlock(D3DXVECTOR3 position)
//{
//	m_pBlockManager = SINSTANCE(CObjectManager)->FindGameObject<CBuildBlock>(_T("B_Block"));
//	int max_X = m_pBlockManager->GetNum_X();
//	int max_Y = m_pBlockManager->GetNum_Y();
//	float Min2;
//	Min2 = 99999;	//�ԕ�
//	D3DXVECTOR3 Dist;
//	//Block�̔z��̎擾
//	for (int idx_Y = 0; idx_Y < max_Y; idx_Y++){
//		for (int idx_X = 0; idx_X < max_X; idx_X++){
//			CBlock* pBlock;
//			pBlock = m_pBlockManager->GetBlocks(idx_X, idx_Y);
//			//�v���C���[��Block�̋����v�Z
//			Dist = pBlock->GetPos() - position;
//
//			float len = D3DXVec3Length(&Dist);
//
//			if (len < Min2)
//			{
//				//��ԋ߂�Block���m��
//				m_lockonBlockIndexW = idx_X;
//				m_lockonBlockIndexH = idx_Y;
//				Min2 = len;//��ԒZ������
//			}
//		}
//	}
//
//	return m_lockonBlockIndexW, m_lockonBlockIndexH;
//}