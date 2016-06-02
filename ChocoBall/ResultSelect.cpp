#include "stdafx.h"
#include "ResultSelect.h"
#include "InputManager.h"
#include "GameObject.h"
#include "ResultCursor.h"
#include "ObjectManager.h"



CResultSelect::CResultSelect()
{
	strcpy(m_pFileName, "image/ACFA.jpg");
}

CResultSelect::~CResultSelect()
{
	
}

void CResultSelect::Initialize(){
	C2DImage::Initialize();
	m_transform.position = D3DXVECTOR3(480.0f, 250.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(80, 45, 0);
	SetAlive(true);
	C2DImage::SetImage();
	m_resultcursor = SINSTANCE(CObjectManager)->FindGameObject<CResultCursor>(_T("ResultCursor"));

}

void CResultSelect::Update(){
	if (m_transform.position.y == m_resultcursor->GetPos().y){
		SetAlpha(1.0f);
	}
	else{
		SetAlpha(0.7f);
	}
}

void CResultSelect::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}