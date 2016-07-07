#include "stdafx.h"
#include "SceneResult.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "GameManager.h"


CSceneResult::CSceneResult()
{
}


CSceneResult::~CSceneResult()
{
}

void CSceneResult::Initialize(){
	m_pInput = SINSTANCE(CInputManager)->GetCurrentInput();
	SINSTANCE(CObjectManager)->AddObject(&m_rBack, _T("ResultBack"), false);
	SINSTANCE(CObjectManager)->AddObject(&m_rSelect[0], _T("Continue"), false);
	m_rSelect[1].SetFileName(_T("image/result_EXIT.png"));
	SINSTANCE(CObjectManager)->AddObject(&m_rSelect[1], _T("GoTitle"), false);
	SINSTANCE(CObjectManager)->AddObject(&m_rCursor, _T("ResultCursor"), false); 
	m_rCursor.SetAudio(m_pAudio);
	SINSTANCE(CObjectManager)->Intialize();
	SINSTANCE(CObjectManager)->FindGameObject<CResultSelect>(_T("GoTitle"))->SetPos(D3DXVECTOR3(790.0f, 400.0f, 0.0f));//Exit‚Ìƒ|ƒWƒVƒ‡ƒ“
	m_IsEnd = false;
}

void CSceneResult::Update(){
	SINSTANCE(CObjectManager)->Update();
	}
void CSceneResult::Draw(){
	SINSTANCE(CObjectManager)->Draw();
}
