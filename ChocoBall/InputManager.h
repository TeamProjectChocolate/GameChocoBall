#pragma once
#include "stdafx.h"
#include "KeyBoard.h"
#include "GamePad.h"

class CInputManager
{
	SINGLETON_DECL(CInputManager);
public:
	//DirectInput�I�u�W�F�N�g�����֐�
	//������: �Ȃ�
	//�Ԃ�l: HRESULT�^ �G���[�R�[�h��ԋp
	//�Ăяo����: SINSTANCE(CInputManager)->DI_Init();
	//���v���O�������ŕK���ŏ��Ɉ�񂾂��Ăяo���Ă�������
	HRESULT WINAPI DI_Init(); 

	//�L�[�{�[�h��DirectInput�f�o�C�X�̐����֐�
	//������: HWND�^ �E�B���h�E�n���h��
	//�Ԃ�l: �Ȃ�
	//�Ăяo����: SINSTANCE(CInputManager)->CreateKeyBoard(g_hWnd);
	//���v���O�������ŕK���ŏ��Ɉ�񂾂��Ăяo���Ă�������
	void CreateInput(HWND hWnd);

	void Add(CKeyBoard*);
	void Add(CGamePad*);

	void SetCurrentInput(CInterface* Input){
		m_currentInput = Input;
	}

	// ���݂̃C���^�[�t�F�[�X���擾����֐�
	CInterface* GetCurrentInput(){
		if (m_currentInput->GetType() == INTERFACE_TYPE::GAMEPAD){
			return static_cast<CGamePad*>(m_currentInput);
		}
		return static_cast<CKeyBoard*>(m_currentInput);
	}

	// �C���^�[�t�F�[�X���؂�ւ���Ă��邩�m�F����֐�
	// �؂�ւ���Ă���Ύ����Ő؂�ւ���
	// ������: CInterface**�^ �C���^�[�t�F�[�X�̃_�u���|�C���^
	// �Ăяo����: SINSTANCE(CInputManager)->IsInputChanged(&m_Input);
	// �����͂��K�v�ȃN���X�ŕK�����t���[���Ăяo���Ă�������
	void IsInputChanged(CInterface** Input){
		if (*Input == m_currentInput){
			return;
		}
		else{
			*Input = GetCurrentInput();
			return;
		}
	}

	void Update();
	void ReleaseObject();
private:
	LPDIRECTINPUT8 m_pInputObject = nullptr;	// DirectInput�I�u�W�F�N�g
	vector<CInterface*> m_Inputs;	// �L�[�{�[�h����������Ε����i�[
	CInterface* m_currentInput = nullptr;	// ���C���̃C���^�[�t�F�[�X
	CInterface* m_SubInput = nullptr;	// �؂�ւ��p�C���^�[�t�F�[�X(���C�����L�[�{�[�h�̎��̓Q�[���p�b�h�A���C�����Q�[���p�b�h�̂Ƃ��̓L�[�{�[�h)
	//vector�ɓo�^���ꂽ�v�f�����ׂč폜����֐�
	//���f�X�g���N�^�ɂČĂяo�����
	void DeleteAll();
};

