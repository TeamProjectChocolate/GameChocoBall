#pragma once

#include "stdafx.h"

typedef enum INTERFACE_TYPE{ KEYBOARD = 0,GAMEPAD };

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
	virtual bool GetConnected() = 0;

	virtual BYTE IsTriggerDecsion() = 0;// ����{�^���������ꂽ��
	virtual BYTE IsPressDecision() = 0;	// ����{�^����������
	virtual BYTE IsTriggerCancel() = 0;	// �L�����Z���A�߂�{�^���������ꂽ��
	virtual BYTE IsPressCancel() = 0;	// �L�����Z���A�߂�{�^����������
	virtual BYTE IsTriggerEscape() = 0;	// �G�X�P�[�v�{�^���������ꂽ��
	virtual BYTE IsPressEscape() = 0;	// �G�X�P�[�v�{�^��������
	virtual BYTE IsTriggerShift() = 0;	// �V�t�g�L�[�������ꂽ��
	virtual BYTE IsPressShift() = 0;	// �V�t�g�L�[������
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

