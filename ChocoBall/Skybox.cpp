#include "stdafx.h"
#include "Skybox.h"
#include "RenderContext.h"


Skybox::Skybox(){
	light.SetAmbientLight(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

}

Skybox::~Skybox(){}

void Skybox::Initialize()
{
	strcpy(m_pFileName, "image/sky.x");
	m_transform.position = D3DXVECTOR3(0.0f, -100.0f, 0.0f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	C3DImage::Initialize();
	SetAlive(true);
	C3DImage::SetImage(); 
}

void Skybox::Update()
{
	C3DImage::Update();
}

void Skybox::Draw()
{
	m_luminance = 1.0f;
	CLight* plight;
	SetUpTechnique();
	plight = SINSTANCE(CRenderContext)->GetCurrentLight();
	SINSTANCE(CRenderContext)->SetCurrentLight(&light);
	C3DImage::Draw();
	SINSTANCE(CRenderContext)->SetCurrentLight(plight);
}