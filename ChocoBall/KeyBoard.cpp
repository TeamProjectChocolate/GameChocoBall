#include "stdafx.h"
#include "KeyBoard.h"
#include "InputManager.h"

CKeyBoard::CKeyBoard()
{
	ClearBuffer();
}

CKeyBoard::~CKeyBoard()
{
}


HRESULT CKeyBoard::CreateInput(HWND hWnd, LPDIRECTINPUT8 InputObject){

	// �L�[�{�[�h�f�o�C�X����
	if (InputObject->CreateDevice(GUID_SysKeyboard, &m_Device, NULL) != DI_OK){
		MessageBox(0, TEXT("DirectInput�L�[�{�[�h�f�o�C�X�������s"), NULL, MB_OK);
		return E_FAIL;
	}
	
	// �t�H�[�}�b�g�Z�b�g
	HRESULT ret = m_Device->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(ret)){
		MessageBox(0, TEXT("�t�H�[�}�b�g�̃Z�b�g�Ɏ��s���܂���"), NULL, MB_OK);
		return E_FAIL;
	}
	
	// �������x���ݒ�
	ret = CDirectInput::CooperativeLevel(hWnd, m_Device);
	if (FAILED(ret)){
		return E_FAIL;
	}

	// �o�b�t�@�T�C�Y�̐ݒ�(�L�[�{�[�h�Ɋւ��Ă̓Q�[���ɂ����ĕs�v�H)
	return S_OK;
}

void CKeyBoard::Update(){
	memcpy(m_KBOldBuf, m_KBNowBuf, sizeof(m_KBNowBuf));
	ZeroMemory(m_KBNowBuf, sizeof(m_KBNowBuf));

	if (FAILED(m_Device->GetDeviceState(sizeof(m_KBNowBuf), m_KBNowBuf))){
		while (m_Device->Acquire() == DIERR_INPUTLOST);		// �A�N�Z�X���擾(�f�o�C�X���X�g���N�����ƃA�N�Z�X�����擾��������)
	}
}

void CKeyBoard::ClearBuffer(){
	ZeroMemory(m_KBNowBuf, sizeof(m_KBNowBuf));
	memcpy(m_KBOldBuf, m_KBNowBuf, sizeof(m_KBNowBuf));
}

BYTE CKeyBoard::GetPrs(const UINT KeyCode)const{
	return (m_KBNowBuf[KeyCode]);
};

BYTE CKeyBoard::GetTrg(const UINT KeyCode)const{
	return (m_KBNowBuf[KeyCode] && !m_KBOldBuf[KeyCode]);
};

BYTE CKeyBoard::IsTriggerDecsion(){ return GetTrg(DIK_RETURN); }
BYTE CKeyBoard::IsPressDecision(){ return GetPrs(DIK_RETURN); }
BYTE CKeyBoard::IsTriggerCancel(){ return GetTrg(DIK_BACK); }
BYTE CKeyBoard::IsPressCancel(){ return GetPrs(DIK_BACK); }
BYTE CKeyBoard::IsTriggerEscape(){ return GetTrg(DIK_ESCAPE); }
BYTE CKeyBoard::IsPressEscape(){ return GetPrs(DIK_ESCAPE); }
BYTE CKeyBoard::IsTriggerLeftShift(){ return GetTrg(DIK_LSHIFT); }
BYTE CKeyBoard::IsPressLeftShift(){ return GetPrs(DIK_LSHIFT); }
BYTE CKeyBoard::IsTriggerRightShift(){ return GetTrg(DIK_RSHIFT); }
BYTE CKeyBoard::IsPressRightShift(){ return GetPrs(DIK_RSHIFT); }
BYTE CKeyBoard::IsTriggerSpace(){ return GetTrg(DIK_SPACE); }
BYTE CKeyBoard::IsPressSpace(){ return GetPrs(DIK_SPACE); }
BYTE CKeyBoard::IsTriggerUp(){ return GetTrg(DIK_UP); }
BYTE CKeyBoard::IsPressUp(){ return GetPrs(DIK_UP); }
BYTE CKeyBoard::IsTriggerDown(){ return GetTrg(DIK_DOWN); }
BYTE CKeyBoard::IsPressDown(){ return GetPrs(DIK_DOWN); }
BYTE CKeyBoard::IsTriggerRight(){ return GetTrg(DIK_RIGHT); }
BYTE CKeyBoard::IsPressRight(){ return GetPrs(DIK_RIGHT); }
BYTE CKeyBoard::IsTriggerLeft(){ return GetTrg(DIK_LEFT); }
BYTE CKeyBoard::IsPressLeft(){ return GetPrs(DIK_LEFT); }