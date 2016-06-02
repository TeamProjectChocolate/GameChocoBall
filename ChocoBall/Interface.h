#pragma once

#include "stdafx.h"

typedef enum INTERFACE_TYPE{ KEYBOARD = 0, GAMEPAD,INTERFACE_NONE = 100 };

class CInterface
{
public:
	CInterface();
	~CInterface();
	virtual void Update() = 0;
	INTERFACE_TYPE GetType(){
		return m_InputType;
	}
	void SetType(INTERFACE_TYPE type){
		m_InputType = type;
	}
	/*
	*	���X�e�B�b�N�̌X���ʂ𐳋K�����ꂽ-1.0�`1.0�Ŏ擾�B�@
	*	���F�}�C�i�X�A�E�F�v���X
	*/
	virtual float GetStickL_XFloat() = 0;
	/*
	*	���X�e�B�b�N�̌X���ʂ𐳋K�����ꂽ-1.0�`1.0�Ŏ擾�B�@
	*	���F�}�C�i�X�A��F�v���X
	*/
	virtual float GetStickL_YFloat() = 0;
	/*
	*	���X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A�E�F�v���X
	*/
	virtual SHORT GetStickL_X() = 0;
	/*
	*	���X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A��F�v���X
	*/
	virtual SHORT GetStickL_Y() = 0;
	/*
	*	�E�X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A�E�F�v���X
	*/
	virtual SHORT GetStickR_X() = 0;
	/*
	*	�E�X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A��F�v���X
	*/
	virtual SHORT GetStickR_Y() = 0;
	/*
	*	���g���K�[�̐[�x
	*  0�`255
	*/
	virtual BYTE  GetTriggerL() = 0;
	/*
	*	�E�g���K�[�̐[�x
	*  0�`255
	*/
	virtual BYTE  GetTriggerR() = 0;

	virtual bool GetConnected() = 0;

	virtual BYTE IsTriggerDecsion() = 0;// ����{�^���������ꂽ��
	virtual BYTE IsPressDecision() = 0;	// ����{�^����������
	virtual BYTE IsTriggerCancel() = 0;	// �L�����Z���A�߂�{�^���������ꂽ��
	virtual BYTE IsPressCancel() = 0;	// �L�����Z���A�߂�{�^����������
	virtual BYTE IsTriggerEscape() = 0;	// �G�X�P�[�v�{�^���������ꂽ��
	virtual BYTE IsPressEscape() = 0;	// �G�X�P�[�v�{�^��������
	virtual BYTE IsTriggerLeftShift() = 0;	// ���V�t�g�L�[�������ꂽ��
	virtual BYTE IsPressLeftShift() = 0;	// ���V�t�g�L�[������
	virtual BYTE IsTriggerRightShift() = 0;	// �E�V�t�g�L�[�������ꂽ��
	virtual BYTE IsPressRightShift() = 0;	// �E�V�t�g�L�[������
	virtual BYTE IsTriggerSpace() = 0;	// �X�y�[�X�L�[�������ꂽ��
	virtual BYTE IsPressSpace() = 0;	// �X�y�[�X�L�[������
	virtual BYTE IsTriggerUp() = 0;		// ���������ꂽ��
	virtual BYTE IsPressUp() = 0;		// ����������
	virtual BYTE IsTriggerDown() = 0;	// ���������ꂽ��
	virtual BYTE IsPressDown() = 0;		// ����������
	virtual BYTE IsTriggerRight() = 0;	// ���������ꂽ��
	virtual BYTE IsPressRight() = 0;	// ����������
	virtual BYTE IsTriggerLeft() = 0;	// ���������ꂽ��
	virtual BYTE IsPressLeft() = 0;		// ����������
private:
	INTERFACE_TYPE m_InputType;
};

