#include "stdafx.h"
#include "SceneTitle.h"
#include "InputManager.h"
#include "ObjectManager.h"


CSceneTitle::CSceneTitle()
{
}


CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Initialize(){
	m_Input = SINSTANCE(CInputManager)->GetInput();
	SINSTANCE(CObjectManager)->AddObject(&m_Back, _T("TitleBack"));
	SINSTANCE(CObjectManager)->AddObject(&m_Select[0], _T("Start"));
	m_Select[1].SetFileName(_T("image/exit.png"));
	SINSTANCE(CObjectManager)->AddObject(&m_Select[1], _T("Exit"));
	SINSTANCE(CObjectManager)->AddObject(&m_Cursor, _T("Cursor"));
	SINSTANCE(CObjectManager)->Intialize();
	SINSTANCE(CObjectManager)->FindGameObject<CTitleSelect>(_T("Exit"))->SetPos(D3DXVECTOR3(500.0f, 350.0f, 0.0f));//Exit‚Ìƒ|ƒWƒVƒ‡ƒ“
}

void CSceneTitle::Update(){
	SINSTANCE(CObjectManager)->Update();
}

void CSceneTitle::Draw(){
	SINSTANCE(CObjectManager)->Draw();
}
