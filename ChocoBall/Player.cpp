#include "Player.h"
#include "InputManager.h"

CPlayer::CPlayer() { }

CPlayer::~CPlayer(){ }

void CPlayer::Initialize()
{
	m_pInput = SINSTANCE(CInputManager)->GetInput();
	m_transform.position = D3DXVECTOR3(0, 1, -17);
	m_transform.angle = D3DXVECTOR3(2, 1, 0);
	m_transform.scale = D3DXVECTOR3(1, 1, 1);
	//m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_pFileName = "image\\Bakuya.x";
	SetAlive(true);
	C3DImage::SetImage();
}

void CPlayer::Initialize(float x,float y)
{
	m_transform.position = D3DXVECTOR3(x, y,-18);
	m_transform.angle = D3DXVECTOR3(2,1,0);
	m_transform.scale = D3DXVECTOR3(1,1,1);
	//m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_pFileName = "image\\Bakuya.x";
	SetAlive(true);
	m_OriginalInit = true;
	C3DImage::SetImage();
}

void CPlayer::Update()
{
<<<<<<< HEAD
	//m_transform.position.z--;
	//m_transform.position.y++;
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_transform.position.x -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_transform.position.x += 0.1f;
	}
=======
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
	//m_transform.angle.y += 0.1f;
>>>>>>> a1aa3cf87bbfca9d4f38796c0a8263d4a683fd2e
	this->SetUp();
}