#include "stdafx.h"
#include "StageManager.h"
#include "GameManager.h"


CStageManager* CStageManager::m_instance = nullptr;

void CStageManager::Initialize()
{
	m_NowStage = STAGE_ID::STAGE_NONE;
	ChangeStage(STAGE_ID::FIRST);
	SetNextStage();
}

void CStageManager::Update()
{
	m_Stage.Update();
}

void CStageManager::Draw()
{
	m_Stage.Draw();
	SetNextStage();
}

void CStageManager::ChangeStage(STAGE_ID id){
	m_NextStage = id;
}

void CStageManager::SetNextStage(){
	if (m_ContinueStage >= STAGE_ID::MAX && m_ContinueStage != STAGE_ID::STAGE_NONE){
		// ÅŒã‚Ü‚ÅƒNƒŠƒA‚µ‚Ä‚¢‚½‚ç‚±‚Ìˆ—‚ð’Ê‚é
		m_IsContinue = false;
		SINSTANCE(CGameManager)->ChangeScene(_T("Title"));
		return;
	}

	if (m_NowStage != m_NextStage){
		if (m_IsContinue){
			m_NowStage = m_ContinueStage;
		}
		else{
			m_NowStage = m_NextStage;
		}
		m_Stage.Initialize(m_pAudio,m_NowStage);
		m_ContinueStage = m_NowStage;
	}
}

void CStageManager::DeleteAll(){
	int size = ARRAYSIZE(StageObjectNumArray);
	for (int idx = 0; idx < size; idx++){
		int size2 = StageObjectNumArray[idx];
		for (int idx2 = 0; idx2 < size2; idx2++){
			SAFE_DELETE(StageGameObject_1[idx2].pObject);
		}
	}
}
