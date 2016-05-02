#include "stdafx.h"
#include "ShadowRender.h"
#include "Effect.h"
#include "GraphicsDevice.h"
#include "RenderContext.h"


CShadowRender* CShadowRender::m_instance = nullptr;

void CShadowRender::Entry(C3DImage* Obj){
	m_ShadowObjects.push_back(Obj);
}

void CShadowRender::Initialize(){
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ShadowTex.hlsl"));	// �g�p����shader�t�@�C�����w��(�f�t�H���g)

	m_pMapZ = nullptr;
	m_pShadow = nullptr;
	m_pOriginalSurf = nullptr;

	// �����_�����O�^�[�Q�b�g����
	(*graphicsDevice()).CreateDepthStencilSurface(WINDOW_WIDTH, WINDOW_HEIGHT, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pMapZ, NULL);
	(*graphicsDevice()).CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pShadow, NULL);
	m_pShadow->GetSurfaceLevel(0, &m_pOriginalSurf);

	m_camera.Initialize();

	// �e�`��p�v���W�F�N�V�����s�񐶐��p�̒l���Z�b�g
	m_camera.SetUpdateType(EUpdateType::enUpdateTypeTarget);
	m_camera.SetNear(1.0f);
	m_camera.SetFar(100.0f);
	m_camera.SetAspect(WINDOW_WIDTH / WINDOW_HEIGHT);
	m_camera.SetViewAngle(D3DXToRadian(60));
}

void CShadowRender::Update(){
	m_camera.SetPos(m_ShadowLightPos);
	m_camera.SetTarget(m_target);
	m_camera.Update();
}

void CShadowRender::Draw(){

	// ���Ƃ̃����_�����O�^�[�Q�b�g��ۑ�
	IDirect3DSurface9* pOldBackBuffer;
	IDirect3DSurface9* pOldZBuffer;

	(*graphicsDevice()).GetRenderTarget(0, &pOldBackBuffer);
	(*graphicsDevice()).GetDepthStencilSurface(&pOldZBuffer);
	
	// �����_�����O�^�[�Q�b�g�̕ύX
	(*graphicsDevice()).SetRenderTarget(0, m_pOriginalSurf);
	(*graphicsDevice()).SetDepthStencilSurface(m_pMapZ);
	
	(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	
	// �I�t�X�N���[�������_�����O
	
	m_pEffect->SetTechnique("ShadowMapping");
	m_pEffect->Begin(NULL, 0);

	for (int idx = 0, size = m_ShadowObjects.size(); idx < size; idx++){
		if (m_ShadowObjects[idx]->GetAlive()){
			m_pEffect->BeginPass(0);
			m_camera.SetCamera(m_pEffect);
			m_pEffect->SetMatrix("World"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &m_ShadowObjects[idx]->GetWorldMatrix()/*�ݒ肵�����s��ւ̃|�C���^*/);
			// ���_�t�H�[�}�b�g���Z�b�g

			IMAGE3D* pImage = m_ShadowObjects[idx]->GetImage();

			(*graphicsDevice()).SetFVF(pImage->pMesh->GetFVF());

			m_pEffect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B

			for (DWORD i = 0; i < pImage->NumMaterials; i++){
				pImage->pMesh->DrawSubset(i);						// ���b�V����`��
			}
			m_pEffect->EndPass();
		}
	}
	m_pEffect->End();
	// �����_�����O�^�[�Q�b�g�����ɖ߂�
	(*graphicsDevice()).SetRenderTarget(0, pOldBackBuffer);
	(*graphicsDevice()).SetDepthStencilSurface(pOldZBuffer);

}

void CShadowRender::DeleteAll(){
	m_ShadowObjects.clear();
}