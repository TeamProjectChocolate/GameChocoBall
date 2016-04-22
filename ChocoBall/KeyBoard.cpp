#include "stdafx.h"
#include "KeyBoard.h"

CKeyBoard::CKeyBoard()
{
}


CKeyBoard::~CKeyBoard()
{
}

HRESULT CKeyBoard::CreateInput(HWND hWnd, LPDIRECTINPUT8 InputObject){

	// キーボードデバイス生成
	if (InputObject->CreateDevice(GUID_SysKeyboard, &m_Device, NULL) != DI_OK){
		MessageBox(0, TEXT("DirectInputキーボードデバイス生成失敗"), NULL, MB_OK);
		return E_FAIL;
	}
	
	// フォーマットセット
	HRESULT ret = m_Device->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(ret)){
		MessageBox(0, TEXT("フォーマットのセットに失敗しました"), NULL, MB_OK);
		return E_FAIL;
	}
	
	// 協調レベル設定
	ret = CDirectInput::CooperativeLevel(hWnd, m_Device);
	if (FAILED(ret)){
		return E_FAIL;
	}

	// バッファサイズの設定(キーボードに関してはゲームにおいて不要？)
	return S_OK;
}

void CKeyBoard::Update(){
	memcpy(m_KBOldBuf, m_KBNowBuf, sizeof(m_KBNowBuf));
	ZeroMemory(m_KBNowBuf, sizeof(m_KBNowBuf));

	if (FAILED(m_Device->GetDeviceState(sizeof(m_KBNowBuf), m_KBNowBuf))){
		while (m_Device->Acquire() == DIERR_INPUTLOST);		// アクセス権取得(デバイスロストを起こすとアクセス権を取得し続ける)
	}
}


BYTE CKeyBoard::GetPrs(const UINT KeyCode)const{
	return (m_KBNowBuf[KeyCode]);
};

BYTE CKeyBoard::GetTrg(const UINT KeyCode)const{
	return (m_KBNowBuf[KeyCode] && !m_KBOldBuf[KeyCode]);
};