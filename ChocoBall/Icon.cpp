#include "stdafx.h"
#include "Icon.h"


CIcon::CIcon()
{
	SetFileName(_T("Image/KILL_icon.png"));
}


CIcon::~CIcon()
{
}

void CIcon::Initialize(){
	C2DImage::Initialize();
	m_transform.position = D3DXVECTOR3(60.0f, 50.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(60.0f, 65.0f, 0.0f);
	SetAlive(true);
	C2DImage::SetImage();
}

void CIcon::Update(){
	
}

void CIcon::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}