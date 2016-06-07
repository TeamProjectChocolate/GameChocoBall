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
	m_rSelect[1].SetFileName(_T("image/Result.jpg"));
	SINSTANCE(CObjectManager)->AddObject(&m_rSelect[1], _T("GoTitle"), false);
	SINSTANCE(CObjectManager)->AddObject(&m_rCursor, _T("ResultCursor"), false); 
	SINSTANCE(CObjectManager)->AddObject(&m_Number, _T("ResultNumber"), false);
	SINSTANCE(CObjectManager)->Intialize();
	SINSTANCE(CObjectManager)->FindGameObject<CResultSelect>(_T("GoTitle"))->SetPos(D3DXVECTOR3(500.0f, 350.0f, 0.0f));//Exitのポジション
	m_IsEnd = false;
}

void CSceneResult::Update(){
	SINSTANCE(CObjectManager)->Update();
	//// リザルト画面終了のお知らせ
	//// 後できちんとif文を追加してねっ！
	//m_IsEnd = true;

	CNumber* pNumber = SINSTANCE(CObjectManager)->FindGameObject<CNumber>(_T("ResultNumber"));
	// 後できちんと条件式を追加する
	if (true){
		pNumber->AddValue(1);
	}
}
void CSceneResult::Draw(){
	SINSTANCE(CObjectManager)->Draw();
}
