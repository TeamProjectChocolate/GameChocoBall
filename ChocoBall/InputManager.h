#pragma once
#include "stdafx.h"
#include "KeyBoard.h"

class CInputManager
{
	SINGLETON_DECL(CInputManager);
public:
	void ReleaseObject();
	HRESULT WINAPI DI_Init();
	void Add(HWND);
	void SelectInterface();
	CDirectInput* GetInput(){
		return m_currentInput;
	}
	void IsPressDecision();	// 決定ボタンが押されたら
private:
	LPDIRECTINPUT8 m_pInputObject;	// DirectInputオブジェクト
	vector<CDirectInput*> m_Inputs;	// キーボードが複数あれば複数格納
	CDirectInput* m_currentInput;
};

