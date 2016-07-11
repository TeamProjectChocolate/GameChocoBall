#include "stdafx.h"
#include "ResultCursor.h"
#include "InputManager.h"
#include "DirectX.h"
#include "GameManager.h"
#include "ResultSelect.h"
#include "ObjectManager.h"



CResultCursor::CResultCursor()
{
	strcpy(m_pFileName, "image/result_CSR.png");
	isup = false;
	isdown = false;
}


CResultCursor::~CResultCursor()
{
}

void CResultCursor::Initialize(){
	C2DImage::Initialize();
	m_pInput = SINSTANCE(CInputManager)->GetCurrentInput();
	m_transform.position = D3DXVECTOR3(620.0f, 300.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(88, 85, 10);
	dir = -1;
	SetAlive(true);
	C2DImage::SetImage();
	t = 1.0f;
}

void CResultCursor::Update(){
	SINSTANCE(CInputManager)->IsInputChanged(&m_pInput);

	if (m_pInput->IsTriggerDecsion() && m_transform.position.y == 300.0f){
		m_pAudio->PlayCue("�I�P�q�b�g", false, this);
		m_pAudio->DeleteAll();
		SINSTANCE(CGameManager)->ChangeScene(_T("Main"));
	}
	
	//if (m_pInput->IsTriggerDecsion() && m_transform.position.y == 400.0f){
	//	m_pAudio->PlayCue("�I�P�q�b�g", false, this);
	//	m_pAudio->DeleteAll();
	//	//MessageBox(0, "�Q�[�����I�����܂���?", NULL, MB_OK);
	//	PostQuitMessage(0);
	//}

	//float Y = m_pInput->GetStickL_YFloat();
	//if (Y>0){
	//	m_transform.position.y = 300.0f;
	//	m_transform.position.x = 620.0f;
	//	if (!isup)
	//	{
	//		m_pAudio->PlayCue("LAPUTA_counter_2", true,this);
	//		isup = true;
	//	}
	//}
	//else
	//{
	//	isup = false;
	//}
	//if (Y<0){
	//	m_transform.position.y = 400.0f;
	//	m_transform.position.x = 600.0f;
	//	if (!isdown)
	//	{
	//		m_pAudio->PlayCue("LAPUTA_counter_2", true,this);
	//		isdown = true;
	//	}
	//	
	//}
	//else
	//{
	//	isdown = false;
	//}
	m_pAudio->Run();
}



void CResultCursor::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}