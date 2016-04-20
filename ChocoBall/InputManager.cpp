#include "stdafx.h"
#include "InputManager.h"


HRESULT WINAPI CInputManager::DI_Init(){
	HRESULT ret = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_pInputObject, NULL);	// DirectInput�̃I�u�W�F�N�g�쐬
	if (FAILED(ret)){
		MessageBox(0, TEXT("DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);
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
