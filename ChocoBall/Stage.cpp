#include "stdafx.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "ShadowRender.h"
#include "ClearText.h"
#include "GameOver.h"
#include "StageManager.h"

CStage::CStage()
{
	m_pPlayer = nullptr;
	m_pAudio = nullptr; 
	m_pEmitter = nullptr;
}

CStage::~CStage()
{
}

void CStage::Initialize(CAudio* pAudio,STAGE_ID NowId)
{
	m_Stage_ID = NowId;
	LPCSTR* ObjectDataArray = StageArray[m_Stage_ID];
	int size = StageObjectNumArray[m_Stage_ID];

	for (int idx = 0; idx < size; idx++){
		if (strcmp(ObjectDataArray[idx], "TESTStage3D") == 0){
			SINSTANCE(CObjectManager)->GenerationObject<CField>(_T(ObjectDataArray[idx]), PRIORTY::OBJECT3D, false);
		}
		else if (strcmp(ObjectDataArray[idx], "BulletPhysics") == 0){
			SINSTANCE(CObjectManager)->GenerationObject<CBulletPhysics>(_T(ObjectDataArray[idx]), PRIORTY::CONFIG, false);
		}
		else if (strcmp(ObjectDataArray[idx], "2DTest") == 0){
			SINSTANCE(CObjectManager)->GenerationObject<CTestObject2D>(_T(ObjectDataArray[idx]), PRIORTY::OBJECT2D_ALPHA, false);
		}
		else if (strcmp(ObjectDataArray[idx], "Number") == 0){
			SINSTANCE(CObjectManager)->GenerationObject<CNumber>(_T(ObjectDataArray[idx]), PRIORTY::OBJECT2D_ALPHA, false);
		}
		else if (strcmp(ObjectDataArray[idx], "Camera") == 0){
			SINSTANCE(CObjectManager)->GenerationObject<CCourceCamera>(_T(ObjectDataArray[idx]), PRIORTY::CONFIG, false);
		}
		else if (strcmp(ObjectDataArray[idx], "EnemyManager") == 0){
			SINSTANCE(CObjectManager)->GenerationObject<CEnemyManager>(_T(ObjectDataArray[idx]), PRIORTY::PLAYER, false);
		}
		else if (strcmp(ObjectDataArray[idx], "TEST3D") == 0){
			SINSTANCE(CObjectManager)->GenerationObject<CPlayer>(_T(ObjectDataArray[idx]), PRIORTY::PLAYER, false);
		}
	}

	SINSTANCE(CObjectManager)->Intialize();
	m_pPlayer = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));

	m_CLevelBuilder.SetIsStage(m_Stage_ID);
	m_CLevelBuilder.Build();

	SINSTANCE(CShadowRender)->Entry(m_pPlayer);
	m_pAudio = pAudio;
	//m_pAudio->PlayCue("ChariotsOfFireBGM");	// 音楽再生

	m_GameState = GAMEEND_ID::CONTINUE;
	m_isGameContinue = true;
}

void CStage::Update()
{
	m_pAudio->Run();		// 音楽更新
	m_GameState = m_pPlayer->GetGameState();

	if (m_isGameContinue){
		if (m_GameState == GAMEEND_ID::CLEAR)
		{
			SINSTANCE(CObjectManager)->GenerationObject<CClearText>(_T("Clear"), PRIORTY::OBJECT2D_ALPHA, false);
			SINSTANCE(CObjectManager)->FindGameObject<CClearText>(_T("Clear"))->Initialize();
			m_isGameContinue = false;
			SINSTANCE(CStageManager)->SetIsContinue(true);
			SINSTANCE(CStageManager)->SetContinueStage(static_cast<STAGE_ID>(m_Stage_ID + 1));
		}
		else if (m_GameState == GAMEEND_ID::OVER)
		{
			SINSTANCE(CObjectManager)->GenerationObject<CGameOver>(_T("GameOver"), PRIORTY::OBJECT2D_ALPHA, false);
			SINSTANCE(CObjectManager)->FindGameObject<CGameOver>(_T("GameOver"))->Initialize();
			m_isGameContinue = false;
			SINSTANCE(CStageManager)->SetIsContinue(true);
		}
	}
	else{
		if (m_GameState == GAMEEND_ID::CLEAR){
			if (SINSTANCE(CObjectManager)->FindGameObject<CClearText>(_T("Clear"))->GetIsEnd()){
				SINSTANCE(CGameManager)->ChangeScene(_T("Result"));
			}
		}
		else if (m_GameState == GAMEEND_ID::OVER){
			if (SINSTANCE(CObjectManager)->FindGameObject<CGameOver>(_T("GameOver"))->GetIsEnd()){
				SINSTANCE(CGameManager)->ChangeScene(_T("Result"));
			}
		}
		
	}
	SINSTANCE(CObjectManager)->Update();
	SINSTANCE(CShadowRender)->Update();
}

void CStage::Draw()
{
	SINSTANCE(CShadowRender)->Draw();
	SINSTANCE(CObjectManager)->Draw();
}
