#include "Player.h"
#include "InputManager.h"


CPlayer::CPlayer() {
	strcpy(m_pFileName, "image/stage.x");
}

CPlayer::~CPlayer(){ }

void CPlayer::Initialize()
{
	C3DImage::Initialize();
	m_pInput = SINSTANCE(CInputManager)->GetInput();
	m_transform.position = D3DXVECTOR3(0, 1, -17);
	m_transform.angle = D3DXVECTOR3(2, 1, 0);
	m_transform.scale = D3DXVECTOR3(1, 1, 1);
	SetAlive(true);
	C3DImage::SetImage();
}

void CPlayer::Initialize(float x,float y)
{
	C3DImage::Initialize();
	m_transform.position = D3DXVECTOR3(x, y,-18);
	m_transform.angle = D3DXVECTOR3(2,1,0);
	m_transform.scale = D3DXVECTOR3(1,1,1);
	SetAlive(true);
	m_OriginalInit = true;
	C3DImage::SetImage();
}

void CPlayer::Update()
{
	if (m_pInput->IsPressUp()){
		m_transform.position.y += 0.05f;
	}
	if (m_pInput->IsPressDown()){
		m_transform.position.y -= 0.05f;
	}
	if (m_pInput->IsPressRight()){
		m_transform.position.x += 0.05f;
	}
	if (m_pInput->IsPressLeft()){
		m_transform.position.x -= 0.05f;
	}
	//m_transform.angle.z += 0.1f;
	C3DImage::Update();
}

void CPlayer::Draw(){
	C3DImage::Draw();
}