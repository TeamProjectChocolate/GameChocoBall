#include "stdafx.h"
#include "TitleCursor.h"
#include "InputManager.h"
#include "DirectX.h"
#include "GameManager.h"



CTitleCursor::CTitleCursor()
{
	strcpy(m_pFileName, "image/ACFA.jpg");
}


CTitleCursor::~CTitleCursor()
{
}

void CTitleCursor::Initialize(){
	C2DImage::Initialize();
	m_Input = SINSTANCE(CInputManager)->GetInput();
	m_transform.position = D3DXVECTOR3(400.0f, 250.0f, 1.0f);
	m_transform.angle = D3DXVECTOR3(0, 0, 0);
	m_transform.scale = D3DXVECTOR3(80, 80, 10);
	SetAlive(true);
	C2DImage::SetImage();
}

void CTitleCursor::Update(){
	if (m_Input->IsTriggerDecsion()&&m_transform.position.y==250.0f){
		SINSTANCE(CGameManager)->ChangeScene(_T("Main"));
	}
	if (m_Input->IsTriggerUp()){
		m_transform.position.y = 250.0f;

	}
	if (m_Input->IsTriggerDecsion() && m_transform.position.y == 350.0f){
			MessageBox(0, "�Q�[�����I�����܂���?", NULL, MB_OK);
			PostQuitMessage(0);
		}
	if (m_Input->IsTriggerDown()){
		m_transform.position.y = 350.0f;
		
	}
}

void CTitleCursor::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}