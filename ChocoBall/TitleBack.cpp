#include "stdafx.h"
#include "TitleBack.h"
#include "InputManager.h"


CTitleBack::CTitleBack()
{
	strcpy(m_pFileName, "image/title.png");
}


CTitleBack::~CTitleBack()
{
}

void CTitleBack::Initialize(){
	C2DImage::Initialize();
	m_transform.position = D3DXVECTOR3(480.0f, 270.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(960, 540, 100);
	SetAlive(true);
	C2DImage::SetImage();
}

void CTitleBack::Update(){
	
}

void CTitleBack::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}