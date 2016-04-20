#include "stdafx.h"
#include "InputManager.h"


HRESULT WINAPI CInputManager::DI_Init(){
	HRESULT ret = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_pInputObject, NULL);	// DirectInputのオブジェクト作成
	if (FAILED(ret)){
		MessageBox(0, TEXT("DirectInputオブジェクトの作成に失敗しました"), NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void CInputManager::Add(HWND hWnd){
	CKeyBoard Input;
	Input.CreateInput(hWnd,m_pInputObject);
}

void CInputManager::ReleaseObject(){
	SAFE_RELEASE(m_pInputObject);
}
