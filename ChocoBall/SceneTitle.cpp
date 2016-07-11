#include "stdafx.h"
#include "SceneTitle.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "GameManager.h"
#include "Audio.h"
#include "ParticleEmitter.h"


CSceneTitle::CSceneTitle()
{
}


CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Initialize(){
	SINSTANCE(CObjectManager)->GenerationObject<CTitleBack>(_T("TitleBack"),PRIORTY::OBJECT2D,false);
	CTitleSelect* start = SINSTANCE(CObjectManager)->GenerationObject<CTitleSelect>(_T("NewGame"),PRIORTY::OBJECT2D_ALPHA,false);
	//CTitleSelect* Continue = SINSTANCE(CObjectManager)->GenerationObject<CTitleSelect>(_T("continue"), PRIORTY::OBJECT2D_ALPHA, false);
	//Continue->SetFileName(_T("image/TAI_EXIT.png"));
	CTitleCursor* cursor = SINSTANCE(CObjectManager)->GenerationObject<CTitleCursor>(_T("Cursor"), PRIORTY::OBJECT2D, false);
	cursor->SetAudio(m_pAudio);
	num = SINSTANCE(CObjectManager)->GenerationObject<CNumber>(_T("Number"), PRIORTY::OBJECT2D_ALPHA, false);
	SINSTANCE(CObjectManager)->Intialize();
	//Continue->SetPos(D3DXVECTOR3(655.0f, 430.0f, 0.0f));//Exit‚Ìƒ|ƒWƒVƒ‡ƒ“
}

void CSceneTitle::Update(){
	int i = CPlayerBullet::EnemyDownNum;
	num->SetValue(i);
	SINSTANCE(CObjectManager)->Update();
}

void CSceneTitle::Draw(){
	SINSTANCE(CObjectManager)->Draw();
}

void CSceneTitle::Release(){

}