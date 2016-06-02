#include "stdafx.h"
#include "GameOver.h"


CGameOver::CGameOver()
{
	strcpy(m_pFileName, "image/over.png");
}


CGameOver::~CGameOver()
{

}

void CGameOver::Initialize(){
	C2DImage::Initialize();
	m_transform.position = D3DXVECTOR3(450.0f, 0.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(100, 80, 100);
	SetAlive(true);
	m_IsEnd = false;
	C2DImage::SetImage();
	
}

void CGameOver::Update(){
	if (m_transform.position.y <= 400){
		m_transform.position.y+=2;
	}
	else{
		m_IsEnd = true;
	}
}

void CGameOver::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}
