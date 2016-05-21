#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "Player.h"
#include "islntersect.h"
#include "Rigidbody.h"

class Bullet : public C3DImage
{
public:
	Bullet::Bullet()
	{
		strcpy(m_pFileName, "image/kyu.x");
	};
	~Bullet();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetUpTechnique()override
	{
		m_pEffect->SetTechnique("NotNormalMapBasicTec");//Texture�������̂ŃZ�b�g�e�N�j�b�N���I�[�o�[���C�h
	};
	void OnDestroy();
	void Build();
private:
	D3DXVECTOR3		m_position;	//�e�̍��W
	D3DXVECTOR3		m_moveSpeed;//�ړ����x�B
	bool			Shotflag;	//�e�����˂���Ă���̂��̃t���O
	CPlayer         m_Player;	//�v���C���[�̃C���X�^���X
	CIsIntersect	m_IsIntersect;	//CIsIntersect�̃C���X�^���X
	CRigidbody      m_Rigidbody;	//CRigidbody�C���X�^���X	
	float			m_radius;
};

