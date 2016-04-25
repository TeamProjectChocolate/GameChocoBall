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
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/Effect00.hlsl"));	// 使用するshaderファイルを指定(デフォルト)
	m_camera.Initialize();
	//m_camera.SetPos(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
	SetAlive(true);
}

void CGameCamera::Update(){
	m_camera.Update();
}

void CGameCamera::Draw(){
	//CGameObject::SetUpTechnique();
	//UINT numPass;
	//m_pEffect->Begin(&numPass/*テクニック内に定義されているパスの数が返却される*/, 0);
	//m_pEffect->BeginPass(0);	//パスの番号を指定してどのパスを使用するか指定
	//m_camera.SetCamera(m_pEffect);
	//m_pEffect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
	//m_pEffect->EndPass();
	//m_pEffect->End();
	SINSTANCE(CRenderContext)->SetCurrentCamera(&m_camera);
}
