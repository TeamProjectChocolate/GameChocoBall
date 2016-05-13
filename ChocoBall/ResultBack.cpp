#include "stdafx.h"
#include "ResultBack.h"
#include "InputManager.h"


CResultBack::CResultBack()
{
	strcpy(m_pFileName, "image/Result.jpg");
}


CResultBack::~CResultBack()
{
}

void CResultBack::Initialize(){
	C2DImage::Initialize();
	m_transform.position = D3DXVECTOR3(650.0f, 300.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(1000, 600, 100);
	SetAlive(true);
	C2DImage::SetImage();
}

void CResultBack::Update(){
	
}

void CResultBack::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}