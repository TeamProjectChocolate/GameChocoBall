#include "stdafx.h"
#include "TitleCursor.h"
#include "InputManager.h"
#include "DirectX.h"
#include "GameManager.h"
#include "TitleSelect.h"
#include "ObjectManager.h"
#include "Player.h"


CTitleCursor::CTitleCursor()
{
	strcpy(m_pFileName, "image/ACFA.jpg");
}


CTitleCursor::~CTitleCursor()
{
	SAFE_DELETE(m_pAudio);
}

void CTitleCursor::Initialize(){
	C2DImage::Initialize();
	m_pAudio = new CAudio;
	m_pAudio->Initialize("Audio/Audio.xgs", "Audio/Audio.xwb", "Audio/Audio.xsb");	// 各種音楽ファイル読込
	m_pAudio->PlayCue("ChariotsOfFireBGM");	// 音楽再生
	m_pInput = SINSTANCE(CInputManager)->GetCurrentInput();
	m_transform.position = D3DXVECTOR3(400.0f, 250.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(80, 80, 10);
	SetAlive(true);
	C2DImage::SetImage();
}

void CTitleCursor::Update(){
	SINSTANCE(CInputManager)->IsInputChanged(&m_pInput);
	m_pAudio->Run();
	if (m_pInput->IsTriggerDecsion() && m_transform.position.y == 250.0f){
		m_pAudio->StopCue("ChariotsOfFireBGM");
		SINSTANCE(CGameManager)->ChangeScene(_T("Main"));
		/*SINSTANCE(CObjectManager)->FindGameObject<CTitleSelect>(_T("Start"))->SetAlpha(1.0f);
		m_transform.scale.x += 20;
		m_transform.scale.y += 20;*/
	}
	if (m_pInput->IsTriggerDecsion() && m_transform.position.y == 350.0f){
		MessageBox(0, "ゲームを終了しますか?", NULL, MB_OK);
		PostQuitMessage(0);
	}
	

	SINSTANCE(CInputManager)->IsInputChanged(&m_pInput);
	float Y = m_pInput->GetStickL_YFloat();
	if (Y>0){
		m_transform.position.y = 250.0f;

	}
	if (Y<0){
		m_transform.position.y = 350.0f;

	}
	


	
}
void CTitleCursor::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}