#pragma once

#include "stdafx.h"
#include "Interface.h"


#define GAMEPAD(Class) Class::getGameInstance()

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )

	//�e�{�^��
#define GAMEPAD_DPAD_UP          0x0001
#define GAMEPAD_DPAD_DOWN        0x0002
#define GAMEPAD_DPAD_LEFT        0x0004
#define GAMEPAD_DPAD_RIGHT       0x0008
#define GAMEPAD_START            0x0010
#define GAMEPAD_BACK             0x0020
#define GAMEPAD_LEFT_THUMB       0x0040
#define GAMEPAD_RIGHT_THUMB      0x0080
#define GAMEPAD_LEFT_SHOULDER    0x0100
#define GAMEPAD_RIGHT_SHOULDER   0x0200
#define GAMEPAD_A                0x1000
#define GAMEPAD_B                0x2000
#define GAMEPAD_X                0x4000
#define GAMEPAD_Y                0x8000


class CGamePad:public CInterface
{
public:
	CGamePad();
	~CGamePad();
	/*
	*	�R���g���[���[���ڑ�����Ă��邩����
	*	�Q�[���̃A�b�v�f�[�g�ŕK���Ă�
	*/
	void Update()override;

	// �o�b�t�@�̍폜
	void ClearBuffer();
	/*
	*	���X�e�B�b�N�̌X���ʂ𐳋K�����ꂽ-1.0�`1.0�Ŏ擾�B�@
	*	���F�}�C�i�X�A�E�F�v���X
	*/
	float GetStickL_XFloat() override
	{
		return (float)GetStickL_X() / 0x7FFF;
	}
	/*
	*	���X�e�B�b�N�̌X���ʂ𐳋K�����ꂽ-1.0�`1.0�Ŏ擾�B�@
	*	���F�}�C�i�X�A��F�v���X
	*/
	float GetStickL_YFloat() override
	{
		return (float)GetStickL_Y() / 0x7FFF;
	}

	/*
	*	���X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A�E�F�v���X
	*/
	SHORT GetStickL_X()override
	{
		if ((m_state.Gamepad.sThumbLX < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbLX > -INPUT_DEADZONE))
		{
			m_state.Gamepad.sThumbLX = 0;
		}
		return m_state.Gamepad.sThumbLX;
	}
	/*
	*	���X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A��F�v���X
	*/
	SHORT GetStickL_Y()override
	{
		if ((m_state.Gamepad.sThumbLY < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbLY > -INPUT_DEADZONE))
		{
			m_state.Gamepad.sThumbLY = 0;
		}
		return m_state.Gamepad.sThumbLY;
	}
	/*
	*	�E�X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A�E�F�v���X
	*/
	SHORT GetStickR_X()override
	{
		if ((m_state.Gamepad.sThumbRX < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbRX > -INPUT_DEADZONE))
		{
			m_state.Gamepad.sThumbRX = 0;
		}
		return m_state.Gamepad.sThumbRX;
	}
	/*
	*	�E�X�e�B�b�N�̌X���ʁ@
	*	���F�}�C�i�X�A��F�v���X
	*/
	SHORT GetStickR_Y()override
	{
		if ((m_state.Gamepad.sThumbRY < INPUT_DEADZONE &&
			m_state.Gamepad.sThumbRY > -INPUT_DEADZONE))
		{
			m_state.Gamepad.sThumbRY = 0;
		}
		return m_state.Gamepad.sThumbRY;
	}

	/*
	*	���g���K�[�̐[�x
	*  0�`255
	*/
	BYTE  GetTriggerL()override
	{
		return m_state.Gamepad.bLeftTrigger;
	}
	/*
	*	�E�g���K�[�̐[�x
	*  0�`255
	*/
	BYTE  GetTriggerR()override
	{
		return m_state.Gamepad.bRightTrigger;
	}
	/*
	*	�R���g���[���[��������Ă��邩
	*/
	bool GetConnected()override
	{
		return m_bConnected;
	}

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
	XINPUT_STATE m_state;	//���
	bool m_bConnected;	//�R���g���[���[����
	WORD m_GPNowBuf;
	WORD m_GPOldBuf;
	// �{�^��������������Ă��邩����
	bool GetPrs(const int& Buttons);
	// �{�^���������ꂽ������
	bool GetTrg(const int& Buttons);
};

