#pragma once
#include "stdafx.h"
#include "KeyBoard.h"

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
	void CreateKeyBoard(HWND hWnd);
	void Add(CDirectInput*);
	void SetCurrentInput(CDirectInput*);
	//void SelectInterface();
	CDirectInput* GetInput(){
		return m_currentInput;
	}
	void Update();
	void ReleaseObject();
private:
	LPDIRECTINPUT8 m_pInputObject = nullptr;	// DirectInput�I�u�W�F�N�g
	vector<CDirectInput*> m_Inputs;	// �L�[�{�[�h����������Ε����i�[
	CDirectInput* m_currentInput= nullptr;

	//vector�ɓo�^���ꂽ�v�f�����ׂč폜����֐�
	//���f�X�g���N�^�ɂČĂяo�����
	void DeleteAll();
};

