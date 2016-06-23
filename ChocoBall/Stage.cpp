#include "stdafx.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "ShadowRender.h"
#include "ClearText.h"
#include "GameOver.h"
#include "StageManager.h"
#include "StageTable.h"
#include "ParticleEmitter.h"

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

	ActivateObjects();

	m_pCamera = SINSTANCE(CObjectManager)->FindGameObject<CCourceCamera>(_T("Camera"));
	m_pCamera->SetStageID(m_Stage_ID);

	m_pEnemyManager = SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager"));
	m_pEnemyManager->SetStageID(m_Stage_ID);

	m_pPlayer = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));
	m_pPlayer->SetStageID(m_Stage_ID);

	SINSTANCE(CObjectManager)->FindGameObject<CField>(_T("TESTStage3D"))->SetStageID(m_Stage_ID);
	SINSTANCE(CObjectManager)->GenerationObject<Skybox>(_T("skybox"), PRIORTY::OBJECT3D, false);
	SINSTANCE(CObjectManager)->GenerationObject<CZBufferSphere>(_T("ZBufferSphere"), PRIORTY::PLAYER, false);

	SINSTANCE(CObjectManager)->Intialize();

	

	CCourceDef* cource = m_pPlayer->GetCourceDef();
	COURCE_BLOCK block = cource->FindCource(cource->EndCource());
	D3DXVECTOR3 workVec = block.endPosition - block.startPosition;
	D3DXVec3Normalize(&workVec, &workVec);
	D3DXVec3Cross(&workVec, &workVec, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXVec3Normalize(&workVec, &workVec);

	CParticleEmitter::EmitterCreate(_T("GoalParticle_Left"), PARTICLE_TYPE::STAR, block.endPosition - (workVec * 2.0f), m_pCamera->GetCamera(), true);
	CParticleEmitter::EmitterCreate(_T("GoalParticle_Right"), PARTICLE_TYPE::STAR, block.endPosition + (workVec * 2.0f), m_pCamera->GetCamera(),true);

	m_CLevelBuilder.SetIsStage(m_Stage_ID);
	m_CLevelBuilder.Build();

	SINSTANCE(CShadowRender)->Entry(m_pPlayer);
	m_pAudio = pAudio;

	m_pAudio->PlayCue(Stage_BGM[m_Stage_ID],false);	// ���y�Đ�
	m_GameState = GAMEEND_ID::CONTINUE;
	m_isGameContinue = true;
}

void CStage::Update()
{
	m_GameState = m_pPlayer->GetGameState();
	m_score.Update();
	m_pCamera->SetGameState(m_GameState);
	if (m_isGameContinue){
		if (m_GameState == GAMEEND_ID::CLEAR)
		{
			SINSTANCE(CObjectManager)->GenerationObject<CClearText>(_T("Clear"), PRIORTY::OBJECT2D_ALPHA, false);
			SINSTANCE(CObjectManager)->FindGameObject<CClearText>(_T("Clear"))->Initialize();
			m_isGameContinue = false;
			SINSTANCE(CStageManager)->SetIsContinue(true);
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
			if (SINSTANCE(CObjectManager)->FindGameObject<CClearText>(_T("Clear"))->GetIsEnd()/* && m_pCamera->GetIsEnd()*/){
				SINSTANCE(CStageManager)->SetContinueStage(static_cast<STAGE_ID>(m_Stage_ID + 1));
				m_pAudio->StopCue(Stage_BGM[m_Stage_ID]);	// ���y�X�g�b�v
				SINSTANCE(CGameManager)->ChangeScene(_T("Result"));
			}
		}
		else if (m_GameState == GAMEEND_ID::OVER){
			if (SINSTANCE(CObjectManager)->FindGameObject<CGameOver>(_T("GameOver"))->GetIsEnd()){
				m_pAudio->StopCue(Stage_BGM[m_Stage_ID]);	// ���y�X�g�b�v
				SINSTANCE(CGameManager)->ChangeScene(_T("Result"));
			}
		}
		
	}
	SINSTANCE(CObjectManager)->Update();
	SINSTANCE(CShadowRender)->Update();
	//m_pAudio->Run();		// ���y�X�V
}

void CStage::Draw()
{
	SINSTANCE(CShadowRender)->Draw();
	SINSTANCE(CObjectManager)->Draw();
}


// �X�e�[�W�Ŏg�p����I�u�W�F�N�g�̏���z��ɒǉ������炱����if����ǉ����邱��
void CStage::ActivateObjects(){
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
}