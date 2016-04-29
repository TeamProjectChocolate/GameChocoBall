#include "MainScene.h"
#include "ObjectManager.h"
#include "GameCamera.h"
#include "Audio.h"
#include "TestObject2D.h"

CMainScene::CMainScene(){
}

CMainScene::~CMainScene(){
}

void CMainScene::Initialize(){
	SINSTANCE(CObjectManager)->GenerationObject<CGameCamera>(_T("3DCamera"), 0);
	SINSTANCE(CObjectManager)->GenerationObject<CTestObject2D>(_T("2DTest"), 3);
	SINSTANCE(CObjectManager)->GenerationObject<CPlayer>(_T("TEST3D"));
	SINSTANCE(CObjectManager)->GenerationObject<CPlayer>(_T("TEST3D2"));
	SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D2"))->SetFileName(_T("image/kyu.x"));
	SINSTANCE(CObjectManager)->Intialize();
	m_pAudio = new CAudio;
	m_pAudio->Initialize("Audio/Audio.xgs", "Audio/Audio.xwb", "Audio/Audio.xsb");	// 各種音楽ファイル読込
	m_pAudio->PlayCue("emiya");	// 音楽再生
}

void CMainScene::Update(){
	m_pAudio->Run();		// 音楽更新
	SINSTANCE(CObjectManager)->Update();
}

void CMainScene::Draw(){
	SINSTANCE(CObjectManager)->Draw();
}
