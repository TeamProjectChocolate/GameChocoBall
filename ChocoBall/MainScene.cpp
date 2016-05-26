#include "stdafx.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "CourceCamera.h"
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


CMainScene::CMainScene(){
}

CMainScene::~CMainScene(){
}

void CMainScene::Initialize(){
	SINSTANCE(CObjectManager)->GenerationObject<CCourceCamera>(_T("Camera"), PRIORTY::CONFIG,true);
	
	extern CEnemyManager g_enemyMgr;
	/*for (short i = 0; i < 20; i++){
		CEnemy* enemy = new CEnemy;
		g_enemyMgr.AddEnemy(enemy);
	}*/
	srand((unsigned int)time(NULL));
	SINSTANCE(CObjectManager)->GenerationObject<CField>(_T("TESTStage3D"), PRIORTY::OBJECT3D,false);
	SINSTANCE(CObjectManager)->GenerationObject<CPlayer>(_T("TEST3D"),PRIORTY::PLAYER,false);
	SINSTANCE(CObjectManager)->GenerationObject<CTestObject2D>(_T("2DTest"), PRIORTY::OBJECT2D,false);
	SINSTANCE(CObjectManager)->AddObject(&g_enemyMgr,_T("EnemyManager"), PRIORTY::PLAYER, false);
	SINSTANCE(CObjectManager)->GenerationObject<CDebri>(_T("Debri"),PRIORTY::OBJECT3D,false);
	//SINSTANCE(CObjectManager)->GenerationObject<Bullet>(_T("Bullet"), PRIORTY::OBJECT3D, false);
	SINSTANCE(CObjectManager)->GenerationObject<CBuildBlock>(_T("B_Block"),PRIORTY::OBJECT3D, false);
	SINSTANCE(CObjectManager)->GenerationObject<CCBManager>(_T("CHOCO"),PRIORTY::OBJECT3D, false);
	SINSTANCE(CObjectManager)->GenerationObject<CNumber>(_T("Number"), PRIORTY::OBJECT2D_ALPHA, false);
	//SINSTANCE(CObjectManager)->GenerationObject<CEnemy>(_T("Enemy"), PRIORTY::OBJECT3D, false);
	m_CLevelBuilder.Build();
	SINSTANCE(CObjectManager)->Intialize();

	SINSTANCE(CShadowRender)->Entry(SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D")));
	m_pAudio = new CAudio;
	m_pAudio->Initialize("Audio/Audio.xgs", "Audio/Audio.xwb", "Audio/Audio.xsb");	// �e�퉹�y�t�@�C���Ǎ�
	//m_pAudio->PlayCue("ChariotsOfFireBGM");	// ���y�Đ�

	m_GameState = GAMEEND_ID::CONTINUE;
	m_isGameContinue = true;
}

void CMainScene::Update(){
	m_pAudio->Run();		// ���y�X�V

	m_Player = (SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D")));
	m_GameState = m_Player->GetGameState();

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
}

void CMainScene::Draw(){
	SINSTANCE(CShadowRender)->Draw();
	SINSTANCE(CObjectManager)->Draw();
}
