#include "stdafx.h"
#include "TitleSelect.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TitleCursor.h"
#include "ObjectManager.h"

CTitleSelect::CTitleSelect()
{
	strcpy(m_pFileName, "image/start.png");
}


CTitleSelect::~CTitleSelect()
{

}

void CTitleSelect::Initialize(){
	C2DImage::Initialize();
	m_Input = SINSTANCE(CInputManager)->GetInput();
	m_transform.position = D3DXVECTOR3(500.0f, 250.0f, 1.0f);
	m_transform.angle = D3DXVECTOR3(0, 0, 0);
	m_transform.scale = D3DXVECTOR3(80, 45, 0);
	SetAlive(true);
	
	C2DImage::SetImage();
	m_cursor = SINSTANCE(CObjectManager)->FindGameObject<CTitleCursor>(_T("Cursor"));

}

void CTitleSelect::Update(){
	if (m_transform.position.y == m_cursor->GetPos().y){
		SetAlpha(1.0f);

	}
	else{
		SetAlpha(0.5f);
	}
}

void CTitleSelect::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}