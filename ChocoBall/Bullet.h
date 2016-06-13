#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "islntersect.h"
#include "Rigidbody.h"
#include "BuildBlock.h"

#define BULLET_LENG 20.0f


class Bullet : public C3DImage
{
public:
	Bullet()
	{
		strcpy(m_pFileName, "image/ball.x");
	};
	~Bullet();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetUpTechnique()override
	{
		m_pEffect->SetTechnique("NormalMapBasicTec");//Texture�������̂ŃZ�b�g�e�N�j�b�N���I�[�o�[���C�h
	};
	void OnDestroy();
	void Build();
	void SetDir(D3DXVECTOR4 dir){
		m_dir = dir;
	}
	void SetBulletSpeed(float Speed)
	{
		m_Speed = Speed;
	}
private:
	D3DXVECTOR3		m_position;	//�e�̍��W
	D3DXVECTOR3		m_moveSpeed;//�ړ����x�B
	bool			Shotflag;	//�e�����˂���Ă���̂��̃t���O
	CIsIntersect	m_IsIntersect;	//CIsIntersect�̃C���X�^���X
	float			m_radius;
	D3DXVECTOR4 m_dir;

	float m_Speed;//�e�̃X�s�[�h
};

