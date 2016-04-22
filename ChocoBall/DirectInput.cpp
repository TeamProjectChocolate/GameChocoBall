#include "stdafx.h"
#include "DirectInput.h"


CDirectInput::CDirectInput(){
}

HRESULT WINAPI CDirectInput::CooperativeLevel(HWND hWnd, LPDIRECTINPUTDEVICE8 pDevice){
	HRESULT ret = pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(ret)){
		MessageBox(0, TEXT("îrëºêßå‰ÉtÉâÉOÇÃéwíËÇ…é∏îsÇµÇ‹ÇµÇΩ"), NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

bool CDirectInput::IsTriggerDecsion(){ return GetTrg(DIK_RETURN); }
bool CDirectInput::IsPressDecision(){ return GetPrs(DIK_RETURN); }
bool CDirectInput::IsTriggerCancel(){ return GetTrg(DIK_BACK); }
bool CDirectInput::IsPressCancel(){ return GetPrs(DIK_BACK); }
bool CDirectInput::IsTriggerUp(){ return GetTrg(DIK_UP); }
bool CDirectInput::IsPressUp(){ return GetPrs(DIK_UP); }
bool CDirectInput::IsTriggerDown(){ return GetTrg(DIK_DOWN); }
bool CDirectInput::IsPressDown(){ return GetPrs(DIK_DOWN); }
bool CDirectInput::IsTriggerRight(){ return GetTrg(DIK_RIGHT); }
bool CDirectInput::IsPressRight(){ return GetPrs(DIK_RIGHT); }
bool CDirectInput::IsTriggerLeft(){ return GetTrg(DIK_LEFT); }
bool CDirectInput::IsPressLeft(){ return GetPrs(DIK_LEFT); }