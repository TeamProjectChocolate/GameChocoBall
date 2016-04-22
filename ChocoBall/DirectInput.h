#pragma once
#include "stdafx.h"

class CDirectInput{
public:
	CDirectInput();
	~CDirectInput(){
		SAFE_RELEASE(m_Device);
	}
	virtual HRESULT CreateInput(HWND, LPDIRECTINPUT8) = 0;
	HRESULT WINAPI CooperativeLevel(HWND, LPDIRECTINPUTDEVICE8);	// DirectInput�r������ݒ菈��
	virtual void Update() = 0;
	virtual bool IsTriggerDecsion();// ����{�^���������ꂽ��
	virtual bool IsPressDecision();	// ����{�^����������
	virtual bool IsTriggerCancel();	// �L�����Z���A�߂�{�^���������ꂽ��
	virtual bool IsPressCancel();	// �L�����Z���A�߂�{�^����������
	virtual bool IsTriggerUp();		// ���������ꂽ��
	virtual bool IsPressUp();		// ����������
	virtual bool IsTriggerDown();	// ���������ꂽ��
	virtual bool IsPressDown();		// ����������
	virtual bool IsTriggerRight();	// ���������ꂽ��
	virtual bool IsPressRight();	// ����������
	virtual bool IsTriggerLeft();	// ���������ꂽ��
	virtual bool IsPressLeft();		// ����������
protected:
	LPDIRECTINPUTDEVICE8 m_Device;
	virtual BYTE GetPrs(const UINT KeyCode)const = 0;	// �L�[����(�������ςȂ�)
	virtual BYTE GetTrg(const UINT KeyCode)const = 0;	// �L�[����(�������u��)
};

//�O���[�o���֐����`���Ăǂ����ɂ�����̂�Ԃ�(�����ł�����DirectInput�I�u�W�F�N�g��Ԃ�)

