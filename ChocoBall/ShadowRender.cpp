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

	for (int idx = 0, size = m_ShadowObjects.size(); idx < size; idx++){
		DrawFrame(m_ShadowObjects[idx]->GetImage()->pModel->GetFrameRoot(), m_ShadowObjects[idx]);
	}

	// �����_�����O�^�[�Q�b�g�����ɖ߂�
	(*graphicsDevice()).SetRenderTarget(0, pOldBackBuffer);
	(*graphicsDevice()).SetDepthStencilSurface(pOldZBuffer);
}

void CShadowRender::DrawFrame(/*LPDIRECT3DDEVICE9 Device,*/LPD3DXFRAME pFrame,C3DImage* pObject){
	LPD3DXMESHCONTAINER pMeshContainer;

	pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer != nullptr){
		DrawMeshContainer(/*Device,*/pMeshContainer/*,pFrame*/,pObject);
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	if (pFrame->pFrameSibling != nullptr){
		DrawFrame(/*Device,*/ pFrame->pFrameSibling,pObject);
	}

	if (pFrame->pFrameFirstChild != nullptr){
		DrawFrame(/*Device,*/ pFrame->pFrameFirstChild,pObject);
	}
}

void CShadowRender::DrawMeshContainer(/*LPDIRECT3DDEVICE9 Device,*/LPD3DXMESHCONTAINER pMeshContainerBase/*,*//*LPD3DXFRAME pFrameBase*/,C3DImage* pObject){
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = static_cast<D3DXMESHCONTAINER_DERIVED*>(pMeshContainerBase);

	// �I�t�X�N���[�������_�����O
	if (pMeshContainer->pSkinInfo != nullptr){
		// �{�[������̉e�̕`��
		AnimationDraw(/*Device, */pMeshContainer/*, pMeshContainerBase, pFrameBase*/,pObject);
	}
	else{
		// �{�[���Ȃ��̉e�̕`��
		NonAnimationDraw(pObject);
	}
}

void CShadowRender::AnimationDraw(D3DXMESHCONTAINER_DERIVED* pMeshContainer,C3DImage* Object){
	if (Object->GetAlive()){

		m_pEffect->SetTechnique("BoneShadowMapping");
		m_pEffect->Begin(NULL, 0);

		//D3DXFRAME_DERIVED* pFrame = static_cast<D3DXFRAME_DERIVED*>(pFrameBase);
		LPD3DXBONECOMBINATION pBoneComb;

		//D3DCAPS9 d3dCaps;
		//Device->GetDeviceCaps(&d3dCaps);
		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
		for (unsigned int iattrib = 0; iattrib < pMeshContainer->NumAttributeGroups; iattrib++){
			for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry){
				DWORD iMatrixIndex = pBoneComb[iattrib].BoneId[iPaletteEntry];
				if (iMatrixIndex != UINT_MAX){
					D3DXMatrixMultiply(
						&g_pBoneMatrices[iPaletteEntry],
						&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
						pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
						);
				}
			}
			m_pEffect->BeginPass(0);

			m_camera.SetCamera(m_pEffect);

			m_pEffect->SetMatrixArray("g_WorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);

			// �{�[���̐�
			m_pEffect->SetFloat("g_numBone", pMeshContainer->NumInfl);

			m_pEffect->CommitChanges();
			pMeshContainer->MeshData.pMesh->DrawSubset(iattrib);
			m_pEffect->EndPass();
		}
		m_pEffect->End();
	}
}

void CShadowRender::NonAnimationDraw(C3DImage* pObject){
	if (pObject->GetAlive()){
		m_pEffect->SetTechnique("BonelessShadowMapping");
		m_pEffect->Begin(NULL, 0);

		m_pEffect->BeginPass(0);
		m_camera.SetCamera(m_pEffect);
		m_pEffect->SetMatrix("World"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &pObject->GetWorldMatrix()/*�ݒ肵�����s��ւ̃|�C���^*/);
		// ���_�t�H�[�}�b�g���Z�b�g

		D3DXMESHCONTAINER_DERIVED* container = pObject->GetImage()->pModel->GetContainer();

		//(*graphicsDevice()).SetFVF(container->pMesh->GetFVF());

		m_pEffect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B

		for (DWORD i = 0; i < container->NumMaterials; i++){
			container->MeshData.pMesh->DrawSubset(i);						// ���b�V����`��
		}
		m_pEffect->EndPass();
		m_pEffect->End();
	}
}

void CShadowRender::DeleteAll(){
	m_ShadowObjects.clear();
}