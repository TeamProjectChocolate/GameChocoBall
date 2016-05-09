#include "stdafx.h"
#include "DirectInput.h"


HRESULT WINAPI CDirectInput::CooperativeLevel(HWND hWnd, LPDIRECTINPUTDEVICE8 pDevice){
	HRESULT ret = pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(ret)){
		MessageBox(0, TEXT("îrëºêßå‰ÉtÉâÉOÇÃéwíËÇ…é∏îsÇµÇ‹ÇµÇΩ"), NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

BYTE CDirectInput::IsTriggerDecsion(){ return GetTrg(DIK_RETURN); }
BYTE CDirectInput::IsPressDecision(){ return GetPrs(DIK_RETURN); }
BYTE CDirectInput::IsTriggerCancel(){ return GetTrg(DIK_BACK); }
BYTE CDirectInput::IsPressCancel(){ return GetPrs(DIK_BACK); }
BYTE CDirectInput::IsTriggerEscape(){ return GetTrg(DIK_ESCAPE); }
BYTE CDirectInput::IsPressEscape(){ return GetPrs(DIK_ESCAPE); }
BYTE CDirectInput::IsTrggerShift(){ return GetTrg(DIK_LSHIFT); }
BYTE CDirectInput::IsPressShift(){ return GetPrs(DIK_LSHIFT); }
BYTE CDirectInput::IsTriggerUp(){ return GetTrg(DIK_UP); }
BYTE CDirectInput::IsPressUp(){ return GetPrs(DIK_UP); }
BYTE CDirectInput::IsTriggerDown(){ return GetTrg(DIK_DOWN); }
BYTE CDirectInput::IsPressDown(){ return GetPrs(DIK_DOWN); }
BYTE CDirectInput::IsTriggerRight(){ return GetTrg(DIK_RIGHT); }
BYTE CDirectInput::IsPressRight(){ return GetPrs(DIK_RIGHT); }
BYTE CDirectInput::IsTriggerLeft(){ return GetTrg(DIK_LEFT); }
BYTE CDirectInput::IsPressLeft(){ return GetPrs(DIK_LEFT); }