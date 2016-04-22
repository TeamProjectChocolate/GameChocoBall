#include "Player.h"

CPlayer::CPlayer() { }

CPlayer::~CPlayer(){ }

void CPlayer::Initialize()
{
	m_transform.position = D3DXVECTOR3(0, 1, -7);
	m_transform.angle = D3DXVECTOR3(1, 0, 0);
	m_transform.scale = D3DXVECTOR3(1, 1, 1);
	//m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_pFileName = "image\\candle.x";
	SetAlive(true);
	C3DImage::SetImage();
}

void CPlayer::Initialize(float x,float y)
{
	m_transform.position = D3DXVECTOR3(x, y,-7);
	m_transform.angle = D3DXVECTOR3(1,0,0);
	m_transform.scale = D3DXVECTOR3(1,1,1);
	//m_backColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	m_pFileName = "image\\candle.x";
	SetAlive(true);
	m_OriginalInit = true;
	C3DImage::SetImage();
}

void CPlayer::Update()
{
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
	this->SetUp();
}