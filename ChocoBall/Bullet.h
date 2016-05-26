#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "islntersect.h"
#include "Rigidbody.h"
#include "LockOn.h"

class CPlayer;
class CEnemyManager;

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
	void BulletPlayerCollision();
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
private:
	D3DXVECTOR3		m_position;	//�e�̍��W
	D3DXVECTOR3		m_moveSpeed;//�ړ����x�B
	bool			Shotflag;	//�e�����˂���Ă���̂��̃t���O
	CPlayer*        m_pPlayer;	//�v���C���[�̃C���X�^���X
	CIsIntersect	m_IsIntersect;	//CIsIntersect�̃C���X�^���X
	CRigidbody      m_Rigidbody;	//CRigidbody�C���X�^���X	
	float			m_radius;
	CLockOn          m_LockOn;
	int				m_lockonEnemyIndex;	//���b�N�I�����Ă���G�̃C���f�b�N�X�B
	bool			m_Hitflag;
};

