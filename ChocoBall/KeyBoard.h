#pragma once
#include "DirectInput.h"

class CKeyBoard :
	public CDirectInput
{
public:
	CKeyBoard();
	~CKeyBoard();
	HRESULT CreateInput(HWND, LPDIRECTINPUT8)override;
	void Update()override;	// �L�[���X�V
private:
	//vector<LPDIRECTINPUTDEVICE8> m_DIKBDevices;	// DirectInput�L�[�{�[�h�f�o�C�X(�����ڑ�����邱�Ƃ��l�����Ĕz��ŊǗ�����)
	//vector<DIDEVICEINSTANCE> m_InstPointer;	// DirectInput��������������C���X�^���X�ւ̃|�C���^�[���i�[����z��
	//int m_DeviceCount;						// �f�o�C�X�����������ł�����
	BYTE GetPrs(const UINT KeyCode)const override;	// �L�[����(�������ςȂ�)
	BYTE GetTrg(const UINT KeyCode)const override;	// �L�[����(�������u��)
	BYTE m_KBOldBuf[256];	// ��u�O�̃L�[�{�[�h���
	BYTE m_KBNowBuf[256];	// ���݂̃L�[�{�[�h���
};

////�O���[�o���֐����`���Ăǂ����ɂ�����̂�Ԃ�(�����ł�����CKeyBoard�N���X�̃C���X�^���X��Ԃ�)
//inline CKeyBoard& KeyBoard()
//{
//	extern CKeyBoard g_KeyboardDevice;
//	return g_KeyboardDevice;
//}
