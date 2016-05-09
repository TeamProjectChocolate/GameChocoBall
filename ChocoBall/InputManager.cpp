#include "stdafx.h"
#include "InputManager.h"


CInputManager* CInputManager::m_instance = nullptr;

HRESULT WINAPI CInputManager::DI_Init(){
	HRESULT ret = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_pInputObject, NULL);	// DirectInputのオブジェクト作成
	if (FAILED(ret)){
		MessageBox(0, TEXT("DirectInputオブジェクトの作成に失敗しました"), NULL, MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

void CInputManager::CreateKeyBoard(HWND hWnd){
	CKeyBoard* Input;
	Input = new CKeyBoard;
	Input->CreateInput(hWnd, m_pInputObject);
	Add(Input);
}

void CInputManager::Add(CDirectInput* Input){
	m_Inputs.push_back(Input);
	SetCurrentInput(Input);
}

void CInputManager::SetCurrentInput(CDirectInput* Input){
	m_currentInput = Input;
}

void CInputManager::Update(){
	m_currentInput->Update();
}

void CInputManager::ReleaseObject(){
	vector<CDirectInput*>::iterator itr = m_Inputs.begin();
	for (itr; itr == m_Inputs.end();){
		(*itr)->~CDirectInput();
		itr = m_Inputs.erase(itr);
	}
	SAFE_RELEASE(m_pInputObject);
}

void CInputManager::DeleteAll(){
	for (int idx = 0, size = m_Inputs.size(); idx < size; idx++){
		SAFE_DELETE(m_Inputs[idx]);
	}
	m_Inputs.clear();
}