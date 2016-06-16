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
	SAFE_DELETE(m_pAudio);
}

void CSceneTitle::Initialize(){

	m_pAudio = new CAudio;
	m_pAudio->Initialize("Audio/Audio.xgs", "Audio/Audio.xwb", "Audio/Audio.xsb");	// 各種音楽ファイル読込
	//m_pAudio->PlayCue("Modern");	// 音楽再生
	//m_pInput = SINSTANCE(CInputManager)->GetInput();
	SINSTANCE(CObjectManager)->AddObject(&m_Back, _T("TitleBack"),false);
	SINSTANCE(CObjectManager)->AddObject(&m_Select[0], _T("NewGame"),false);
	m_Select[1].SetFileName(_T("image/continue.png"));
	SINSTANCE(CObjectManager)->AddObject(&m_Select[1], _T("Continue"),false);
	SINSTANCE(CObjectManager)->AddObject(&m_Cursor, _T("Cursor"),false);
	SINSTANCE(CObjectManager)->Intialize();
	SINSTANCE(CObjectManager)->FindGameObject<CTitleSelect>(_T("Continue"))->SetPos(D3DXVECTOR3(745.0f, 430.0f, 0.0f));//Exitのポジション
}

void CSceneTitle::Update(){
	SINSTANCE(CObjectManager)->Update();
}

void CSceneTitle::Draw(){
	SINSTANCE(CObjectManager)->Draw();
}
