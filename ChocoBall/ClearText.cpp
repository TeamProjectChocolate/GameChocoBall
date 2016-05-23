#include"stdafx.h"
#include "ClearText.h"


CClearText::CClearText()
{
	strcpy(m_pFileName, "image/clear.png");
}


CClearText::~CClearText()
{

}

void CClearText::Initialize(){
	C2DImage::Initialize();
	m_transform.position = D3DXVECTOR3(450.0f, 400.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(800, 800, 100);
	C2DImage::SetImage();
	dir = -1;
	t = 0.0f;
}

void CClearText::Update(){
	if (t <= 1.0f)
	{
		dir = 1;
	}
	t += 0.015f * dir;
	SetAlpha(t);
}

void CClearText::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}
