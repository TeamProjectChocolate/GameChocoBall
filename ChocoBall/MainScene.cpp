#include "stdafx.h"
#include "MainScene.h"
#include "ObjectManager.h"
#include "GameCamera.h"
#include "Audio.h"
#include "TestObject2D.h"
#include "Field.h"
#include "ShadowRender.h"
#include "Debri.h"

CMainScene::CMainScene(){
}

CMainScene::~CMainScene(){
}

void CMainScene::Initialize(){
	SINSTANCE(CObjectManager)->GenerationObject<CGameCamera>(_T("3DCamera"), PRIORTY::CONFIG,true);
	SINSTANCE(CObjectManager)->GenerationObject<CField>(_T("TESTStage3D"), PRIORTY::OBJECT3D,false);
	SINSTANCE(CObjectManager)->GenerationObject<CPlayer>(_T("TEST3D"),PRIORTY::PLAYER,false);
	SINSTANCE(CObjectManager)->GenerationObject<CTestObject2D>(_T("2DTest"), PRIORTY::OBJECT2D,false);
	SINSTANCE(CObjectManager)->GenerationObject<CEnemy>(_T("ENEMY"), PRIORTY::PLAYER, false);
	SINSTANCE(CObjectManager)->GenerationObject<CDebri>(_T("Debri"),false);
	SINSTANCE(CObjectManager)->Intialize();

	SINSTANCE(CShadowRender)->Entry(SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D")));
	m_pAudio = new CAudio;
	m_pAudio->Initialize("Audio/Audio.xgs", "Audio/Audio.xwb", "Audio/Audio.xsb");	// 各種音楽ファイル読込
	m_pAudio->PlayCue("emiya");	// 音楽再生
}

void CMainScene::Update(){
	m_pAudio->Run();		// 音楽更新
	SINSTANCE(CObjectManager)->Update();
	SINSTANCE(CShadowRender)->Update();
}

void CMainScene::Draw(){
	SINSTANCE(CShadowRender)->Draw();
	SINSTANCE(CObjectManager)->Draw();
}
