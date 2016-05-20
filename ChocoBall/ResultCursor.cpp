#include "stdafx.h"
#include "ResultCursor.h"
#include "InputManager.h"
#include "DirectX.h"
#include "GameManager.h"
#include "ResultSelect.h"
#include "ObjectManager.h"



CResultCursor::CResultCursor()
{
	strcpy(m_pFileName, "image/Result.jpg");
}


CResultCursor::~CResultCursor()
{
}

void CResultCursor::Initialize(){
	C2DImage::Initialize();
	m_Input = SINSTANCE(CInputManager)->GetCurrentInput();
	m_transform.position = D3DXVECTOR3(400.0f, 250.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(100, 80, 10);
	dir = -1;
	SetAlive(true);
	C2DImage::SetImage();
	t = 1.0f;
}

void CResultCursor::Update(){
	SINSTANCE(CInputManager)->IsInputChanged(&m_Input);

	if (m_Input->IsTriggerDecsion() && m_transform.position.y == 250.0f){
		SINSTANCE(CGameManager)->ChangeScene(_T("Main"));
	}
	if (m_Input->IsTriggerDecsion() && m_transform.position.y == 350.0f){
		SINSTANCE(CGameManager)->ChangeScene(_T("Title"));
	}
	if (m_Input->IsTriggerUp()){
		m_transform.position.y = 250.0f;

	}
	if (m_Input->IsTriggerDecsion() && m_transform.position.y == 350.0f){
		MessageBox(0, "ƒQ[ƒ€‚ðI—¹‚µ‚Ü‚·‚©?", NULL, MB_OK);
		PostQuitMessage(0);
	}
	if (m_Input->IsTriggerDown()){
		m_transform.position.y = 350.0f;

	}
}

void CResultCursor::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}