#include "stdafx.h"
#include "TitleBack.h"
#include "InputManager.h"


CTitleBack::CTitleBack()
{
	strcpy(m_pFileName, "image/noborin.png");
}


CTitleBack::~CTitleBack()
{
}

void CTitleBack::Initialize(){
	C2DImage::Initialize();
	m_Input = SINSTANCE(CInputManager)->GetInput();
	m_transform.position = D3DXVECTOR3(100.100f, 100.0f, 1.0f);
	m_transform.angle = D3DXVECTOR3(1, 1, 1);
	m_transform.scale = D3DXVECTOR3(100, 100, 100);
	SetAlive(true);
	C2DImage::SetImage();
}

void CTitleBack::Update(){
	if (m_Input->IsPressUp()){

	}
	if (m_Input->IsPressDown()){

	}
	if (m_Input->IsPressLeft()){

	}
	if (m_Input->IsPressRight()){

	}
}

void CTitleBack::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();

}