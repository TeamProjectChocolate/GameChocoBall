#include "stdafx.h"
#include "C3DImage.h"
#include "Effect.h"
#include "ImageManager.h"
#include "RenderContext.h"
#include "Camera.h"
#include "GraphicsDevice.h"
#include "ShadowRender.h"
#include "SkinModelData.h"
#include "AllocateHierarchy.h"

HRESULT C3DImage::SetImage(){

	m_pImage = SINSTANCE(CImageManager)->Find3DImage(m_pFileName);
	if (m_pImage != nullptr){
		if (m_pImage->pModel->GetAnimationController() != nullptr){
			m_animation.Initialize(m_pImage->pModel->GetAnimationController());
		}
	}
	else{
		LoadXFile();
	}
	m_currentAnimNo = 0;
	m_animation.PlayAnimation(m_currentAnimNo, 1.0f);
	return S_OK;
}

HRESULT C3DImage::LoadXFile(){
	CSkinModelData* pSkinModelData = new CSkinModelData;
	pSkinModelData->LoadModelData(m_pFileName,&m_animation);
	m_pImage = new IMAGE3D;
	m_pImage->pModel = pSkinModelData;
	SINSTANCE(CImageManager)->Add3D(m_pFileName, pSkinModelData);
	return S_OK;
}

void C3DImage::Initialize(){
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ModelShader.hlsl"));	// 使用するshaderファイルを指定(デフォルト)
	m_hEyePosition = m_pEffect->GetParameterByName(NULL, "EyePosition");
	m_hWorldMatrixArray = m_pEffect->GetParameterByName(nullptr, "g_WorldMatrixArray");
	m_hluminance = m_pEffect->GetParameterByName(nullptr, "g_luminance");
	m_hnumBone = m_pEffect->GetParameterByName(nullptr, "g_numBone");
	m_hAlpha = m_pEffect->GetParameterByName(nullptr, "Alpha");
	m_hRota = m_pEffect->GetParameterByName(nullptr, "Rota");
	m_hWorld = m_pEffect->GetParameterByName(nullptr, "World");
	m_hTexture = m_pEffect->GetParameterByName(nullptr, "g_Texture");
	m_hShadowMap = m_pEffect->GetParameterByName(nullptr, "g_ShadowMap");
}

void C3DImage::Update(){
	UpdateFrame(graphicsDevice(), m_pImage->pModel->GetFrameRoot());
	m_animation.Update(DELTA_TIME);
}

void C3DImage::UpdateFrame(LPDIRECT3DDEVICE9 Device, LPD3DXFRAME pFrame){
	AnimationUpdate();
}

void C3DImage::AnimationUpdate(){
	D3DXMATRIX Trans;	// 移動行列
	D3DXMATRIX Scale;	// 拡大・縮小行列
	D3DXMatrixIdentity(&m_World);	// 行列初期化

	D3DXMatrixRotationQuaternion(&m_World, &m_transform.angle);	// クォータニオンによる回転行列の作成

	m_Rota = m_World;

	D3DXMatrixScaling(&Scale, m_transform.scale.x, m_transform.scale.y, m_transform.scale.z);
	D3DXMatrixMultiply(&m_World, &Scale, &m_World);

	D3DXMatrixTranslation(&Trans, m_transform.position.x, m_transform.position.y, m_transform.position.z);
	D3DXMatrixMultiply(&m_World, &m_World, &Trans);

	
	if (m_pImage->pModel){
		m_pImage->pModel->UpdateBoneMatrix(&m_World);	//ボーン行列を更新。
	}
}

void C3DImage::Draw(){
	DrawFrame(m_pImage->pModel->GetFrameRoot());
}

void C3DImage::DrawFrame(LPD3DXFRAME pFrame){
	LPD3DXMESHCONTAINER pMeshContainer;

	pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer != nullptr){
		DrawMeshContainer(pMeshContainer,pFrame);
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	if (pFrame->pFrameSibling != nullptr){
		DrawFrame(pFrame->pFrameSibling);
	}

	if (pFrame->pFrameFirstChild != nullptr){
		DrawFrame(pFrame->pFrameFirstChild);
	}
}

void C3DImage::DrawMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase,LPD3DXFRAME pFrameBase){
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = static_cast<D3DXMESHCONTAINER_DERIVED*>(pMeshContainerBase);

	if (pMeshContainer->pSkinInfo != nullptr){
		// スキン情報あり
		AnimationDraw(pMeshContainer,pFrame);
	}
	else{
		// スキン情報なし
		NonAnimationDraw(pFrame);
	}
}

void C3DImage::AnimationDraw(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXFRAME_DERIVED* pFrame){

	LPD3DXBONECOMBINATION pBoneComb;
	SetUpTechniqueAnimation();
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
		m_pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
		m_pEffect->BeginPass(0);

		SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);
		SINSTANCE(CRenderContext)->GetCurrentLight()->SetLight(m_pEffect);
		m_pEffect->SetMatrixArray(m_hWorldMatrixArray, g_pBoneMatrices, pMeshContainer->NumPaletteEntries);

		SINSTANCE(CShadowRender)->SetShadowCamera(m_pEffect);
		m_pEffect->SetFloat(m_hluminance, m_luminance);

		// ボーンの数
		m_pEffect->SetFloat(m_hnumBone, pMeshContainer->NumInfl);
		m_pEffect->SetTexture(m_hTexture, pMeshContainer->ppTextures[pBoneComb[iattrib].AttribId]);

		m_pEffect->CommitChanges();
		pMeshContainer->MeshData.pMesh->DrawSubset(iattrib);
		m_pEffect->EndPass();
		m_pEffect->End();
	}

}

void C3DImage::NonAnimationDraw(D3DXFRAME_DERIVED* pFrame){

	D3DXMATRIX World;
	if (pFrame != nullptr){
		if (m_UseBorn){
			World = pFrame->CombinedTransformationMatrix;
		}
		else{
			World = m_World;
		}
	}

	D3DXMESHCONTAINER_DERIVED* container = m_pImage->pModel->GetContainer();
	if (container->ppTextures == nullptr){
		m_pEffect->SetTechnique("NotNormalMapBasicTec");
	}
	
	SetUpTechnique();

	UINT numPass;
	m_pEffect->Begin(&numPass/*テクニック内に定義されているパスの数が返却される*/, 0);
	m_pEffect->BeginPass(0);	//パスの番号を指定してどのパスを使用するか指定

	// 透明度有効化
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 現在のプロジェクション行列とビュー行列をシェーダーに転送
	SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);
	SINSTANCE(CRenderContext)->GetCurrentLight()->SetLight(m_pEffect);
	// 視点をシェーダーに転送
	m_pEffect->SetVector(m_hEyePosition, reinterpret_cast<D3DXVECTOR4*>(&SINSTANCE(CRenderContext)->GetCurrentCamera()->GetPos()));

	
	SINSTANCE(CShadowRender)->SetShadowCamera(m_pEffect);
	//ここで固定描画と同じように、ローカル座標に設定された頂点群をデバイスに渡す。通常と同じ方法。
	//	メッシュも同じく、マテリアルやテクスチャを設定
	//DrawSubset()を呼び出して描画

	// ワールドトランスフォーム(絶対座標変換)
	// ワールド行列生成


	m_pEffect->SetMatrix(m_hRota, &m_Rota);
	m_pEffect->SetMatrix(m_hWorld/*エフェクトファイル内の変数名*/, &World/*設定したい行列へのポインタ*/);

	m_pEffect->SetFloat(m_hAlpha, GetAlpha());
	m_pEffect->SetFloat(m_hluminance, m_luminance);
	for (DWORD i = 0; i < container->NumMaterials; i++){
		m_pEffect->SetTexture(m_hShadowMap, SINSTANCE(CShadowRender)->GetTexture());	// テクスチャ情報をセット
		m_pEffect->SetTexture(m_hTexture, container->ppTextures[i]);	// テクスチャ情報をセット
		//m_pEffect->SetTexture("g_normalMap", SINSTANCE(CImageManager)->Find2DImage(_T("image/normal.jpg"))->pTex);
		m_pEffect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。
		container->MeshData.pMesh->DrawSubset(i);						// メッシュを描画
	}
	m_pEffect->EndPass();
	m_pEffect->End();
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}