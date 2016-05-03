#include "stdafx.h"
#include "TitleBack.h"
#include "InputManager.h"


CTitleBack::CTitleBack()
{
	strcpy(m_pFileName, "image/ACFA.jpg");
}


CTitleBack::~CTitleBack()
{
}

void CTitleBack::Initialize(){
	C2DImage::Initialize();
	m_Input = SINSTANCE(CInputManager)->GetInput();
	m_transform.position = D3DXVECTOR3(450.0f, 400.0f, 1.0f);
	m_transform.angle = D3DXVECTOR3(0, 0, 0);
	m_transform.scale = D3DXVECTOR3(800, 800, 100);
	SetAlive(true);
	C2DImage::SetImage();
}

void CTitleBack::Update(){
	
}

void CTitleBack::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}