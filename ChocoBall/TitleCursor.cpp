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
	strcpy(m_pFileName, "image/arrow.png");
}


CTitleCursor::~CTitleCursor()
{
}

void CTitleCursor::Initialize(){
	C2DImage::Initialize();
	m_pInput = SINSTANCE(CInputManager)->GetCurrentInput();
	m_transform.position = D3DXVECTOR3(510.0f, 300.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(75, 80, 10);
	SetAlive(true);
	C2DImage::SetImage();
}

void CTitleCursor::Update(){
	SINSTANCE(CInputManager)->IsInputChanged(&m_pInput);
	if (m_pInput->IsTriggerDecsion() && m_transform.position.y == 300.0f){
		SINSTANCE(CGameManager)->ChangeScene(_T("Main"));
		/*SINSTANCE(CObjectManager)->FindGameObject<CTitleSelect>(_T("Start"))->SetAlpha(1.0f);
		m_transform.scale.x += 20;
		m_transform.scale.y += 20;*/
	}
	if (m_pInput->IsTriggerDecsion() && m_transform.position.y == 430.0f){
		PostQuitMessage(0);
	}
	

	SINSTANCE(CInputManager)->IsInputChanged(&m_pInput);
	float Y = m_pInput->GetStickL_YFloat();
	if (Y>0){
		m_transform.position.y = 300.0f;
		m_transform.position.x = 510.0f;

	}
	if (Y<0){
		m_transform.position.y = 430.0f;
		m_transform.position.x = 592.0f;
	}
	


	
}
void CTitleCursor::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}