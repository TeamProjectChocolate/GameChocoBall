#include "stdafx.h"
#include "TitleSelect.h"
#include "InputManager.h"


CTitleSelect::CTitleSelect()
{
	strcpy(m_pFileName, "image/start.png");
}


CTitleSelect::~CTitleSelect()
{

}

void CTitleSelect::Initialize(){
	C2DImage::Initialize();
	m_transform.position = D3DXVECTOR3(500.0f, 250.0f, 1.0f);
	SetRotation(0.0f);
	m_transform.scale = D3DXVECTOR3(80, 45, 0);
	SetAlive(true);
	C2DImage::SetImage();


}

void CTitleSelect::Update(){
	/*if (m_alpha)
	m_alpha -= 0.009;*/

	
	// オブジェクトの透明度(デフォルトは1、透明度を指定したい場合は継承先で任意の値を設定してください)
}

void CTitleSelect::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}