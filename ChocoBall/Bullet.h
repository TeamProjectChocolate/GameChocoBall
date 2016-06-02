#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "islntersect.h"
#include "Rigidbody.h"
#include "LockOn.h"
#include "BuildBlock.h"
#include "EnemyManager.h"


class  CPlayer;

class Bullet : public C3DImage
{
public:
	Bullet()
	{
		strcpy(m_pFileName, "image/kyu.x");
	};
	~Bullet();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void BulletEnemyCollision();

	void BulletBlockCollision();
	void SetUpTechnique()override
	{
		m_pEffect->SetTechnique("NotNormalMapBasicTec");//Texture�������̂ŃZ�b�g�e�N�j�b�N���I�[�o�[���C�h
	};
	void OnDestroy();
	void Build();
	bool GetHitflag()
	{
		return m_Hitflag;
	}
	void SetDir(D3DXVECTOR4 dir){
		m_dir = dir;
	}

private:
	D3DXVECTOR3		m_position;	//�e�̍��W
	D3DXVECTOR3		m_moveSpeed;//�ړ����x�B
	bool			Shotflag;	//�e�����˂���Ă���̂��̃t���O
	CIsIntersect	m_IsIntersect;	//CIsIntersect�̃C���X�^���X
	float			m_radius;

	CLockOn          m_LockOn;
	int				m_lockonEnemyIndex;	//���b�N�I�����Ă���G�̃C���f�b�N�X�B
	bool			m_Hitflag;
	D3DXVECTOR4 m_dir;
	CEnemyManager* m_pEnemyManager;
	CBuildBlock* m_pBlockManager;
};
