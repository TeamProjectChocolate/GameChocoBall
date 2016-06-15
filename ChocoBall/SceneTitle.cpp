#include "stdafx.h"
#include "SceneTitle.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "Audio.h"
#include "ParticleEmitter.h"


CSceneTitle::CSceneTitle()
{
}


CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Initialize(){
	m_pAudio = new CAudio;
	m_pAudio->Initialize("Audio/Audio.xgs", "Audio/Audio.xwb", "Audio/Audio.xsb");	// �e�퉹�y�t�@�C���Ǎ�
	m_pAudio->PlayCue("ChariotsOfFireBGM");	// ���y�Đ�
	//m_pInput = SINSTANCE(CInputManager)->GetInput();
	SINSTANCE(CObjectManager)->AddObject(&m_Back, _T("TitleBack"),false);
	SINSTANCE(CObjectManager)->AddObject(&m_Select[0], _T("Start"),false);
	m_Select[1].SetFileName(_T("image/�^�C�g��Continue.png"));
	SINSTANCE(CObjectManager)->AddObject(&m_Select[1], _T("Exit"),false);
	SINSTANCE(CObjectManager)->AddObject(&m_Cursor, _T("Cursor"),false);
	SINSTANCE(CObjectManager)->Intialize();
	SINSTANCE(CObjectManager)->FindGameObject<CTitleSelect>(_T("Exit"))->SetPos(D3DXVECTOR3(630.0f, 350.0f, 0.0f));//Exit�̃|�W�V����
}

void CSceneTitle::Update(){
	m_pAudio->Run();
	SINSTANCE(CObjectManager)->Update();
}

void CSceneTitle::Draw(){
	SINSTANCE(CObjectManager)->Draw();
}
