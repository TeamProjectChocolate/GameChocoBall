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
	void ClearBuffer();
	/*
	*	���X�e�B�b�N�̌X���ʂ𐳋K�����ꂽ-1.0�`1.0�Ŏ擾�B�@
	*	���F�}�C�i�X�A�E�F�v���X
	*/
	float GetStickL_XFloat() override
	{
		if (IsPressRight())
		{
			return 1.0f;
		}
		else if (IsPressLeft()){
			return -1.0f;
		}
		return 0.0f;
	}
	/*
	*	���X�e�B�b�N�̌X���ʂ𐳋K�����ꂽ-1.0�`1.0�Ŏ擾�B�@
	*	���F�}�C�i�X�A��F�v���X
	*/
	float GetStickL_YFloat() override
	{
		if (IsPressUp())
		{
			return 1.0f;
		}
		else if (IsPressDown()){
			return -1.0f;
		}
		return 0.0f;
	}
	/*
	*	���X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A�E�F�v���X
	*/
	SHORT GetStickL_X()override
	{
		if (IsPressRight())
		{
			return static_cast<SHORT>(IsPressRight());
		}
		return static_cast<SHORT>(IsPressLeft());
	}
	/*
	*	���X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A��F�v���X
	*/
	SHORT GetStickL_Y()override
	{
		if (IsPressUp())
		{
			return static_cast<SHORT>(IsPressUp());
		}
		return static_cast<SHORT>(IsPressDown());
	}
	/*
	*	�E�X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A�E�F�v���X
	*/
	SHORT GetStickR_X()override
	{
		return 0;
	}
	/*
	*	�E�X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A��F�v���X
	*/
	SHORT GetStickR_Y()override
	{
		return 0;
	}

	/*
	*	���g���K�[�̐[�x
	*  0�`255
	*/
	BYTE  GetTriggerL()override
	{
		return GetPrs(DIK_LCONTROL);
	}
	/*
	*	�E�g���K�[�̐[�x
	*  0�`255
	*/
	BYTE  GetTriggerR()override
	{
		return GetPrs(DIK_RCONTROL);
	}

	bool GetConnected()override{ return true; };
	BYTE IsTriggerDecsion()override;// ����{�^���������ꂽ��
	BYTE IsPressDecision()override;	// ����{�^����������
	BYTE IsTriggerCancel()override;	// �L�����Z���A�߂�{�^���������ꂽ��
	BYTE IsPressCancel()override;	// �L�����Z���A�߂�{�^����������
	BYTE IsTriggerEscape()override;	// �G�X�P�[�v�{�^���������ꂽ��
	BYTE IsPressEscape()override;	// �G�X�P�[�v�{�^��������
	BYTE IsTriggerLeftShift()override;	// ���V�t�g�L�[�������ꂽ��
	BYTE IsPressLeftShift()override;	// ���V�t�g�L�[������
	BYTE IsTriggerRightShift()override;	// �E�V�t�g�L�[�������ꂽ��
	BYTE IsPressRightShift()override;	// �E�V�t�g�L�[������
	BYTE IsTriggerSpace()override;	// �X�y�[�X�L�[�������ꂽ��
	BYTE IsPressSpace()override;	// �X�y�[�X�L�[������
	BYTE IsTriggerUp()override;		// ���������ꂽ��
	BYTE IsPressUp()override;		// ����������
	BYTE IsTriggerDown()override;	// ���������ꂽ��
	BYTE IsPressDown()override;		// ����������
	BYTE IsTriggerRight()override;	// ���������ꂽ��
	BYTE IsPressRight()override;	// ����������
	BYTE IsTriggerLeft()override;	// ���������ꂽ��
	BYTE IsPressLeft()override;		// ����������
private:
	//vector<LPDIRECTINPUTDEVICE8> m_DIKBDevices;	// DirectInput�L�[�{�[�h�f�o�C�X(�����ڑ�����邱�Ƃ��l�����Ĕz��ŊǗ�����)
	//vector<DIDEVICEINSTANCE> m_InstPointer;	// DirectInput��������������C���X�^���X�ւ̃|�C���^�[���i�[����z��
	//int m_DeviceCount;						// �f�o�C�X�����������ł�����
	BYTE GetPrs(const UINT KeyCode)const;	// �L�[����(�������ςȂ�)
	BYTE GetTrg(const UINT KeyCode)const;	// �L�[����(�������u��)
	BYTE m_KBOldBuf[256];	// ��u�O�̃L�[�{�[�h���
	BYTE m_KBNowBuf[256];	// ���݂̃L�[�{�[�h���
};
