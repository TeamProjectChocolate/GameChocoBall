#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "ShadowRender.h"



CPlayer::CPlayer() {
	strcpy(m_pFileName, "image/TestPlayer.x");
}

CPlayer::~CPlayer(){ }

void CPlayer::Initialize()
{
	C3DImage::Initialize();
	m_pInput = SINSTANCE(CInputManager)->GetInput();
	m_transform.position = D3DXVECTOR3(0, 1, -17);
	SetRotation(D3DXVECTOR3(0, 1, 0),0.1f);
	m_transform.scale = D3DXVECTOR3(1, 1, 1);
	SetAlive(true);
	SetAlpha(0.5f);
	C3DImage::SetImage();
}

void CPlayer::Update()
{
	if (m_pInput->IsPressShift() && m_pInput->IsPressUp()){
		m_transform.position.y += 0.05f;
		SetRotation(D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXToRadian(90.0f));
	}
	else if (m_pInput->IsPressUp()){
		m_transform.position.z += 0.05f;
		SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(180.0f));
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressDown()){
		m_transform.position.y -= 0.05f;
		SetRotation(D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXToRadian(-90.0f));
	}
	else if (m_pInput->IsPressDown()){
		m_transform.position.z -= 0.05f;
		SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(0.0f));
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressRight()){
		
	}
	else if (m_pInput->IsPressRight()){
		m_transform.position.x += 0.05f;
		SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(-90.0f));
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressLeft()){
	}
	else if (m_pInput->IsPressLeft()){
		m_transform.position.x -= 0.05f;
		SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(90.0f));
	}
	C3DImage::Update();
	SINSTANCE(CShadowRender)->SetObjectPos(m_transform.position);
	SINSTANCE(CShadowRender)->SetShadowCameraPos(m_transform.position + D3DXVECTOR3(0.0f, 10.0f, 0.0f));
}

void CPlayer::Draw(){
	SetUpTechnique();
	C3DImage::Draw();
}