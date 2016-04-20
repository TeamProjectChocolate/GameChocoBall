#pragma once
#include "Infomation.h"

class CGameObject
{
public:
	CGameObject();
	~CGameObject();
	virtual void SetSprite(LPD3DXSPRITE){};	// ���z�֐�:�p���悪2D�N���X�Ȃ�p����N���X�Œ��g������
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void SetAlive(bool alive){
		m_alive = alive;
	}
	bool GetAlive(){
		return m_alive;
	}
	short GetType(){
		return m_ObjecType;
	}
	bool GetOriginal(){
		return m_OriginalInit;
	}
protected:
	LPCSTR m_pFileName;		// �ǂݍ��ރt�@�C���̖��O���i�[����
	TRANSEFORM m_transform; // �I�u�W�F�N�g�̍��W�A��]�A�傫�����
	bool m_alive;			// �����t���O(true�Ȃ琶���Afalse�Ȃ玀�S)
	short m_ObjecType;		// �I�u�W�F�N�g��2D��3D���������ϐ�(0�Ȃ�2D,1�Ȃ�3D)
// �I�[�o�[���[�h�������t���O
// (�p����̃N���X��Initialize�֐��̃I�[�o�[���[�h���g�p�����ꍇ�́A���̃t���O��true�ɂ��Ă�������)
	bool m_OriginalInit;
};

