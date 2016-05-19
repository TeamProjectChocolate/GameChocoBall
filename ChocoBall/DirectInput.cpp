#include "stdafx.h"
#include "DirectInput.h"


HRESULT WINAPI CDirectInput::CooperativeLevel(HWND hWnd, LPDIRECTINPUTDEVICE8 pDevice){
	HRESULT ret = pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(ret)){
		MessageBox(0, TEXT("�r������t���O�̎w��Ɏ��s���܂���"), NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

