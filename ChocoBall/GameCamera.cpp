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
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/Effect00.hlsl"));	// �g�p����shader�t�@�C�����w��(�f�t�H���g)
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
	//m_pEffect->Begin(&numPass/*�e�N�j�b�N���ɒ�`����Ă���p�X�̐����ԋp�����*/, 0);
	//m_pEffect->BeginPass(0);	//�p�X�̔ԍ����w�肵�Ăǂ̃p�X���g�p���邩�w��
	//m_camera.SetCamera(m_pEffect);
	//m_pEffect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
	//m_pEffect->EndPass();
	//m_pEffect->End();
	SINSTANCE(CRenderContext)->SetCurrentCamera(&m_camera);
}
