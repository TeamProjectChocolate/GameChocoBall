#pragma once
#include "stdafx.h"
#include "Interface.h"

class CDirectInput:public CInterface{
public:
	CDirectInput(){
		m_Device = nullptr;
	};
	~CDirectInput(){
		SAFE_RELEASE(m_Device);
	}
	virtual HRESULT CreateInput(HWND, LPDIRECTINPUT8) = 0;
	HRESULT WINAPI CooperativeLevel(HWND, LPDIRECTINPUTDEVICE8);	// DirectInput�r������ݒ菈��
protected:
	LPDIRECTINPUTDEVICE8 m_Device;
};

//�O���[�o���֐����`���Ăǂ����ɂ�����̂�Ԃ�(�����ł�����DirectInput�I�u�W�F�N�g��Ԃ�)

