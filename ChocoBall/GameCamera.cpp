#include "stdafx.h"
#include "GameCamera.h"
#include "RenderContext.h"


CGameCamera::CGameCamera()
{
}


CGameCamera::~CGameCamera()
{
}

void CGameCamera::Initialize(){
	//m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ModelShader.hlsl"));	// 使用するshaderファイルを指定(デフォルト)
	m_camera.Initialize();
	SetAlive(true);
}

void CGameCamera::Update(){
	m_camera.Update();
}

void CGameCamera::Draw(){
	SINSTANCE(CRenderContext)->SetCurrentCamera(&m_camera);
}
