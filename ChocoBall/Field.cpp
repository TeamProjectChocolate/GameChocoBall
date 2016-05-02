#include "stdafx.h"
#include "Field.h"


CField::CField()
{
	strcpy(m_pFileName, "image/stage.x");
}


CField::~CField()
{
}

void CField::Initialize(){
	C3DImage::Initialize();
	m_transform.position = D3DXVECTOR3(0,0.6, -16.5);
	m_transform.angle = D3DXVECTOR3(2.5, 1.65, 2.48);
	m_transform.scale = D3DXVECTOR3(1, 1, 1);
	SetAlive(true);
	C3DImage::SetImage();
}

void CField::Update(){
	C3DImage::Update();
}

void CField::Draw(){
	SetUpTechnique();
	C3DImage::Draw();
}