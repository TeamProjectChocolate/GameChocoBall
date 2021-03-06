#include "stdafx.h"
#include "DirectInput.h"


HRESULT WINAPI CDirectInput::CooperativeLevel(HWND hWnd, LPDIRECTINPUTDEVICE8 pDevice){
	HRESULT ret = pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(ret)){
		MessageBox(0, TEXT("排他制御フラグの指定に失敗しました"), NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

