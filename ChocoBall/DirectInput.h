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
	virtual BYTE KBGetPrs(const UINT KeyCode)const = 0;	// �L�[����(�������ςȂ�)
	virtual BYTE KBGetTrg(const UINT KeyCode)const = 0;	// �L�[����(�������u��)
protected:
	LPDIRECTINPUTDEVICE8 m_Device;
};

//�O���[�o���֐����`���Ăǂ����ɂ�����̂�Ԃ�(�����ł�����DirectInput�I�u�W�F�N�g��Ԃ�)

