
#include "stdafx.h"

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
	m_transform.position = D3DXVECTOR3(450.0f, 250.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(800, 800, 100);
	C2DImage::SetImage();
	SetAlive(true);
	dir = -1;
	t = 0.0f;
	m_IsEnd = false;
}

void CClearText::Update(){
	if (t <= 1.0f)
	{
		t += 0.015f;
	}
	else{
		m_IsEnd = true;
	}
	SetAlpha(t);
}

void CClearText::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}
