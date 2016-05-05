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

	
	// �I�u�W�F�N�g�̓����x(�f�t�H���g��1�A�����x���w�肵�����ꍇ�͌p����ŔC�ӂ̒l��ݒ肵�Ă�������)
}

void CTitleSelect::Draw(){
	C2DImage::SetupMatrices();
	C2DImage::Draw();
}