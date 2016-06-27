#include "stdafx.h"
#include "TitleSelect.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TitleCursor.h"
#include "ObjectManager.h"

CTitleSelect::CTitleSelect()
{
	strcpy(m_pFileName, "image/TAI_START.png");
}


CTitleSelect::~CTitleSelect()
{

}

void CTitleSelect::Initialize(){
	C2DImage::Initialize();
	m_transform.position = D3DXVECTOR3(595.0f, 300.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(310, 84, 0);
	SetAlive(true);
	dir = -1;
	C2DImage::SetImage();
	m_cursor = SINSTANCE(CObjectManager)->FindGameObject<CTitleCursor>(_T("Cursor"));
	t = 1.0f;

}

void CTitleSelect::Update(){
	if (m_transform.position.y == m_cursor->GetPos().y){
		if (t >= 1.0f){
			dir = -1;
		}
		else if (t <= 0.0f)
		{
			dir = 1;
		}
		t += 0.015f * dir;
		SetAlpha(t);
	}
	else{
		dir = -1;
		t = 1.0f;
		SetAlpha(1.0f);
	}	
}

void CTitleSelect::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}