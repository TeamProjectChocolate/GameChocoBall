#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "Chocoball.h"
#include "GameObject.h"
#include "Player.h"

#define CHOCO_NUM 200		//���ɗ����`���R�̐�


//Chocoball���Ǘ�����N���X
class CCBManager : public CGameObject{
public:
	void Initialize();
	void Update();
	void Draw();

	//�i�s�������Z�b�g���܂��B
	void SetVector(D3DXVECTOR3 vec)
	{
		m_Vector = vec;
	}

	//�ŏ��̃|�W�V�������擾�ł��܂��B
	D3DXVECTOR3 GetStartPosition()
	{
		return m_pos;
	}

	//�ŏ��̃|�W�V�������Z�b�g���܂��B
	void SetStartPosition(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	//�I�_�̃|�W�V�������Z�b�g���܂��B
	void SetEndPosition(D3DXVECTOR3 Epos)
	{
		m_posG = Epos;
	}

	//�I�_�̃|�W�V�������擾�ł��܂��B
	D3DXVECTOR3 GetEndPosition()
	{
		return m_posG;
	}
	//�`���R�{�[���Ƃ̏Փ˔���B
	bool IsHit(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	
private:
	D3DXVECTOR3			m_pos;			//���������ꏊ�̃|�W�V�����B
	D3DXVECTOR3			m_posG;			//����Ă�����(�S�[��)�̃|�W�V�����B
	D3DXVECTOR3			m_Vector;		//�`���R�̐i�s�����B
	CChocoBall			m_Choco[CHOCO_NUM];
	float				m_interval;		//�C���^�[�o�[���B
	float				m_timer;		//�^�C�}�[�B
	int					m_numCreate;	//�쐬�ς݂̃`���R�{�[���̐��B
};