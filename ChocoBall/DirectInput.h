#pragma once
#include "stdafx.h"

class CDirectInput{
public:
	CDirectInput(){
		m_Device = nullptr;
	};
	~CDirectInput(){
		SAFE_RELEASE(m_Device);
	}
	virtual HRESULT CreateInput(HWND, LPDIRECTINPUT8) = 0;
	HRESULT WINAPI CooperativeLevel(HWND, LPDIRECTINPUTDEVICE8);	// DirectInput�r������ݒ菈��
	virtual void Update() = 0;
	virtual BYTE IsTriggerDecsion();// ����{�^���������ꂽ��
	virtual BYTE IsPressDecision();	// ����{�^����������
	virtual BYTE IsTriggerCancel();	// �L�����Z���A�߂�{�^���������ꂽ��
	virtual BYTE IsPressCancel();	// �L�����Z���A�߂�{�^����������
	virtual BYTE IsTriggerEscape();	// �G�X�P�[�v�{�^���������ꂽ��
	virtual BYTE IsPressEscape();	// �G�X�P�[�v�{�^��������
	virtual BYTE IsTriggerShift();	// �V�t�g�L�[�������ꂽ��
	virtual BYTE IsPressShift();	// �V�t�g�L�[������
	virtual BYTE IsTriggerSpace();	// �X�y�[�X�L�[�������ꂽ��
	virtual BYTE IsPressSpace();	// �X�y�[�X�L�[������
	virtual BYTE IsTriggerUp();		// ���������ꂽ��
	virtual BYTE IsPressUp();		// ����������
	virtual BYTE IsTriggerDown();	// ���������ꂽ��
	virtual BYTE IsPressDown();		// ����������
	virtual BYTE IsTriggerRight();	// ���������ꂽ��
	virtual BYTE IsPressRight();	// ����������
	virtual BYTE IsTriggerLeft();	// ���������ꂽ��
	virtual BYTE IsPressLeft();		// ����������
protected:
	LPDIRECTINPUTDEVICE8 m_Device;
	virtual BYTE GetPrs(const UINT KeyCode)const = 0;	// �L�[����(�������ςȂ�)
	virtual BYTE GetTrg(const UINT KeyCode)const = 0;	// �L�[����(�������u��)
};

//�O���[�o���֐����`���Ăǂ����ɂ�����̂�Ԃ�(�����ł�����DirectInput�I�u�W�F�N�g��Ԃ�)

