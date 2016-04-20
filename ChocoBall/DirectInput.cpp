#include "stdafx.h"
#include "DirectInput.h"

LPDIRECTINPUT8 Input = NULL;		// DirectInput�I�u�W�F�N�g
LPDIRECTINPUTDEVICE8 g_1pDIDevice = NULL;
HRESULT ret;
BYTE m_KBOldBuf[256];
BYTE m_KBNowBuf[256];

CDirectInput::CDirectInput(){}
CDirectInput::~CDirectInput(){
	g_1pDIDevice->Release();
	Input->Release();
}

HRESULT WINAPI CDirectInput::DI_Init(HWND hWnd){

	ret = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&Input, NULL);	// DirectInput�̃I�u�W�F�N�g�쐬
	if (FAILED(ret)){
		MessageBox(0, TEXT("DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);
		return E_FAIL;		// �쐬�Ɏ��s
	}

	ret = Input->CreateDevice(GUID_SysKeyboard, &g_1pDIDevice, NULL);	// DirectInput�̃f�o�C�X�쐬
	if FAILED(ret){
		MessageBox(0, TEXT("DirectInput�f�o�C�X�̍쐬�Ɏ��s���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	ret = g_1pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	if FAILED(ret){
		MessageBox(0, TEXT("�t�H�[�}�b�g�̃Z�b�g�Ɏ��s���܂���"), NULL, MB_OK);
		return E_FAIL;
	}

	ret = g_1pDIDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if FAILED(ret){
		MessageBox(0, TEXT("�r������t���O�̎w��Ɏ��s���܂���"), NULL, MB_OK);
		return E_FAIL;
	}


	
	return S_OK;
}

void CDirectInput::Update(){
	memcpy(m_KBOldBuf, m_KBNowBuf, sizeof(m_KBNowBuf));
	ZeroMemory(m_KBNowBuf, sizeof(m_KBNowBuf));
	
	if (FAILED(g_1pDIDevice->GetDeviceState(sizeof(m_KBNowBuf), m_KBNowBuf))){
		while (g_1pDIDevice->Acquire() == DIERR_INPUTLOST);
	}
}

BYTE CDirectInput::KBGetPrs(const UINT KeyCode)const{
	return (m_KBNowBuf[KeyCode]);
};

BYTE CDirectInput::KBGetTrg(const UINT KeyCode)const{
	return (m_KBNowBuf[KeyCode] && !m_KBOldBuf[KeyCode]);
};