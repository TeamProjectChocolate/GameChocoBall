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
}

CStage::~CStage()
{
}

void CStage::Initialize(CAudio* pAudio,STAGE_ID NowId)
{
	m_Stage_ID = NowId;
	GENERATION_OBJECT_DATA* ObjectDataArray = StageArray[m_Stage_ID];
	int size = StageObjectNumArray[m_Stage_ID];

	for (int idx = 0; idx < size; idx++){
		SINSTANCE(CObjectManager)->AddObject(
				ObjectDataArray[idx].pObject,
				ObjectDataArray[idx].ObjectName,
				ObjectDataArray[idx].priorty,
				ObjectDataArray[idx].IsCommon
			);
	}



	SINSTANCE(CObjectManager)->Intialize();
	m_pPlayer = (SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D")));

	m_CLevelBuilder.SetIsStage(m_Stage_ID);
	m_CLevelBuilder.Build();

	SINSTANCE(CShadowRender)->Entry(m_pPlayer);
	m_pAudio = pAudio;
	//m_pAudio->PlayCue("ChariotsOfFireBGM");	// ���y�Đ�

	m_GameState = GAMEEND_ID::CONTINUE;
	m_isGameContinue = true;

}

void CStage::Update()
{
	m_pAudio->Run();		// ���y�X�V
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
		// �N���A�e�L�X�g��Q�[���I�[�o�[�e�L�X�g�������������H
		// ���������������K������if�����A�N�e�B�u�����邱��
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
