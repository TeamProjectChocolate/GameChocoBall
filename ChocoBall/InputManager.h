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
	void IsPressDecision();	// ����{�^���������ꂽ��
private:
	LPDIRECTINPUT8 m_pInputObject;	// DirectInput�I�u�W�F�N�g
	vector<CDirectInput*> m_Inputs;	// �L�[�{�[�h����������Ε����i�[
	CDirectInput* m_currentInput;
};

