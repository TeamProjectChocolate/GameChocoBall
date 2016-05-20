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
	for (short i = 0; i < 20; i++){
		CEnemy* enemy = new CEnemy;
		g_enemyMgr.AddEnemy(enemy);
	}
	srand((unsigned int)time(NULL));
	SINSTANCE(CObjectManager)->GenerationObject<CField>(_T("TESTStage3D"), PRIORTY::OBJECT3D,false);
	SINSTANCE(CObjectManager)->GenerationObject<CPlayer>(_T("TEST3D"),PRIORTY::PLAYER,false);
	SINSTANCE(CObjectManager)->GenerationObject<CTestObject2D>(_T("2DTest"), PRIORTY::OBJECT2D,false);
	SINSTANCE(CObjectManager)->AddObject(&g_enemyMgr,_T("EnemyManager"), PRIORTY::PLAYER, false);
	SINSTANCE(CObjectManager)->GenerationObject<CDebri>(_T("Debri"),PRIORTY::OBJECT3D,false);
	SINSTANCE(CObjectManager)->GenerationObject<Bullet>(_T("Bullet"), PRIORTY::OBJECT3D, false);
	SINSTANCE(CObjectManager)->GenerationObject<CBuildBlock>(_T("B_Block"),PRIORTY::OBJECT3D, false);
	SINSTANCE(CObjectManager)->GenerationObject<CCBManager>(_T("CHOCO"),PRIORTY::OBJECT3D, false);
	SINSTANCE(CObjectManager)->GenerationObject<CNumber>(_T("Number"), PRIORTY::OBJECT2D_ALPHA, false);
	SINSTANCE(CObjectManager)->Intialize();

	SINSTANCE(CShadowRender)->Entry(SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D")));
	m_pAudio = new CAudio;
	m_pAudio->Initialize("Audio/Audio.xgs", "Audio/Audio.xwb", "Audio/Audio.xsb");	// 各種音楽ファイル読込
	//m_pAudio->PlayCue("ChariotsOfFireBGM");	// 音楽再生
}

void CMainScene::Update(){
	m_pAudio->Run();		// 音楽更新
	//static bool flg = true;
	//if (flg){
	//	SINSTANCE(CObjectManager)->GenerationObject<CResult>(_T("Clear"), 3, false);
	//	flg = false;
	//}
	SINSTANCE(CObjectManager)->Update();
	SINSTANCE(CShadowRender)->Update();
}

void CMainScene::Draw(){
	SINSTANCE(CShadowRender)->Draw();
	SINSTANCE(CObjectManager)->Draw();
}
