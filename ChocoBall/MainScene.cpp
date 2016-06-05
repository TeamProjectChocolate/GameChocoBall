#include "stdafx.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "Audio.h"
#include "TestObject2D.h"
#include "Field.h"
#include "ShadowRender.h"
#include "Debri.h"
#include "Block.h"
#include "BuildBlock.h"
#include "Result.h"
#include "ClearText.h"
#include "GameOver.h"
#include "Number.h"
#include "EnemyManager.h"
#include "CBManager.h"
#include "StageManager.h"
#include "Score.h"


CMainScene::CMainScene(){
}

CMainScene::~CMainScene(){
}

void CMainScene::Initialize(){
	srand((unsigned int)time(NULL));
	SINSTANCE(CStageManager)->Initialize();
}

void CMainScene::Update(){
	m_pAudio->Run();		// ‰¹ŠyXV
	m_Player = (SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D")));
	m_GameState = m_Player->GetGameState();
	m_score.Update();
	if (m_isGameContinue){
		if (m_GameState == GAMEEND_ID::CLEAR)
		{
			SINSTANCE(CObjectManager)->GenerationObject<CClearText>(_T("Clear"), PRIORTY::OBJECT2D_ALPHA, false);
			SINSTANCE(CObjectManager)->FindGameObject<CClearText>(_T("Clear"))->Initialize();
			m_isGameContinue = false;
		}
		else if (m_GameState == GAMEEND_ID::OVER)
		{
			SINSTANCE(CObjectManager)->GenerationObject<CGameOver>(_T("GameOver"), PRIORTY::OBJECT2D_ALPHA, false);
			SINSTANCE(CObjectManager)->FindGameObject<CGameOver>(_T("GameOver"))->Initialize();
			m_isGameContinue = false;
		}
	}

	SINSTANCE(CObjectManager)->Update();
	SINSTANCE(CShadowRender)->Update();
	SINSTANCE(CStageManager)->Update();
}

void CMainScene::Draw(){
	SINSTANCE(CStageManager)->Draw();
}
