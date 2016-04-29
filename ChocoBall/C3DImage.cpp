#include "C3DImage.h"
#include "Effect.h"
#include "ImageManager.h"
#include "RenderContext.h"
#include "Camera.h"
#include "GraphicsDevice.h"

HRESULT C3DImage::SetImage(){
	IMAGE3D* Image = SINSTANCE(CImageManager)->Find3DImage(m_pFileName);
	if (Image != nullptr){
		m_NumMaterials = Image->NumMaterials;
		m_pMeshMat = Image->pMat;
		m_pMeshTex = Image->ppTex;
		m_pMesh = Image->pMesh;
		return S_OK;
	}

	LoadXFile();
	return S_OK;
}

HRESULT C3DImage::ReSet(){
	IMAGE3D* Image = SINSTANCE(CImageManager)->Find3DImage(m_pFileName);
	if (Image != nullptr){
		m_NumMaterials = Image->NumMaterials;
		m_pMeshMat = Image->pMat;
		m_pMeshTex = Image->ppTex;
		m_pMesh = Image->pMesh;
		return S_OK;
	}

	LoadXFile();
	return S_OK;
}

HRESULT C3DImage::LoadXFile(){
	DWORD i;

	// Xファイルロード
	if (FAILED(D3DXLoadMeshFromX(m_pFileName, D3DXMESH_MANAGED, graphicsDevice(), NULL, &m_pMaterials, NULL, &m_NumMaterials, &m_pMesh))){		// Xファイル読み取り
		return E_FAIL;
	};

	// Xファイルに法線がない場合は、法線を書き込む
	if (!(m_pMesh->GetFVF() & D3DFVF_NORMAL)){
		ID3DXMesh* pTempMesh = NULL;
		m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF() | D3DFVF_NORMAL, graphicsDevice(), &pTempMesh);
		D3DXComputeNormals(pTempMesh, NULL);
		m_pMesh->Release();
		m_pMesh = pTempMesh;
	}

	// マテリアル、テクスチャの準備
	m_pMeshMat = new D3DMATERIAL9[m_NumMaterials];		// メッシュ情報を確保
	m_pMeshTex = new LPDIRECT3DTEXTURE9[m_NumMaterials];		// テクスチャを確保

	D3DXMATERIAL* d3Mat = (D3DXMATERIAL*)m_pMaterials->GetBufferPointer();

	for (i = 0; i < m_NumMaterials; i++){
		m_pMeshMat[i] = d3Mat[i].MatD3D;		// マテリアル情報セット
		m_pMeshMat[i].Ambient = m_pMeshMat[i].Diffuse;		// 環境光初期化

		m_pMeshTex[i] = NULL;		// テクスチャ初期化
		if (d3Mat[i].pTextureFilename != NULL && lstrlen(d3Mat[i].pTextureFilename) > 0){		// 使用しているテクスチャがあれば読み込む

			if (FAILED(D3DXCreateTextureFromFile(graphicsDevice(), d3Mat[i].pTextureFilename, &m_pMeshTex[i]))){
				return E_FAIL;
			}
		}
	}

	SINSTANCE(CImageManager)->Add3D(m_pFileName, m_pMeshMat, m_pMeshTex, m_NumMaterials, m_pMesh);		// IMAGE情報配列に追加
	m_pMaterials->Release();		// マテリアル情報解放
	return S_OK;
}

void C3DImage::Initialize(){
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ModelShader.hlsl"));	// 使用するshaderファイルを指定(デフォルト)


	//// レンダリングターゲット生成？
	//(*graphicsDevice()).CreateDepthStencilSurface(WINDOW_WIDTH, WINDOW_HEIGHT, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pMapZ, NULL);
	//(*graphicsDevice()).CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pShadow, NULL);
	//m_pShadow->GetSurfaceLevel(0, &m_pOriginalSurf);


	m_lightDir[0] = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	m_lightDir[1] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_lightDir[2] = D3DXVECTOR3(1.0f, -1.0f, 0.5f);
	m_lightDir[3] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(m_lightDir[0].x, m_lightDir[0].y, m_lightDir[0].z, 0.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(m_lightDir[1].x, m_lightDir[1].y, m_lightDir[1].z, 0.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(m_lightDir[2].x, m_lightDir[2].y, m_lightDir[2].z, 0.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(m_lightDir[3].x, m_lightDir[3].y, m_lightDir[3].z, 0.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));

	m_light.SetAmbientLight(D3DXVECTOR4(0.2f, 0.0f, 0.0f,100.0f));

	count = 0;
	dir = D3DXVECTOR3(1,1,1);
}

void C3DImage::Update(){
	if (m_lightDir[0].x > 1.0f){
		dir.x *= -1;
	}
	else if (m_lightDir[0].x < -1.0f){
		dir.x *= -1;
	}
	m_lightDir[0].x += 0.1f * dir.x;

	if (m_lightDir[0].y > 1.0f){
		dir.y *= -1;
	}
	else if (m_lightDir[0].y < -1.0f){
		dir.y *= -1;
	}
	m_lightDir[0].y += 0.1f * dir.y;

	if (m_lightDir[0].z > 1.0f){
		dir.z *= -1;
	}
	else if (m_lightDir[0].z < -1.0f){
		dir.z *= -1;
	}
	m_lightDir[0].z += 0.1f * dir.z;

	if (count % 60 == 0){
		D3DXVECTOR3 work = m_lightDir[0];
		m_lightDir[0] = m_lightDir[1];
		m_lightDir[1] = m_lightDir[2];
		m_lightDir[2] = m_lightDir[3];
		m_lightDir[3] = work;
		count = 0;
	}

	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(m_lightDir[0].x, m_lightDir[0].y, m_lightDir[0].z, 0.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(m_lightDir[1].x, m_lightDir[1].y, m_lightDir[1].z, 0.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(m_lightDir[2].x, m_lightDir[2].y, m_lightDir[2].z, 0.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(m_lightDir[3].x, m_lightDir[3].y, m_lightDir[3].z, 0.0f));

	count++;
}

void C3DImage::Draw(){

	D3DXMATRIX Trans;	// 移動行列
	D3DXMATRIX Rota;	// 回転行列
	D3DXMATRIX Scale;	// 拡大・縮小行列

	D3DXMatrixIdentity(&mWorld);	// 行列初期化

	D3DXMatrixScaling(&Scale, m_transform.scale.x, m_transform.scale.y, m_transform.scale.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Scale);

	D3DXMatrixRotationX(&Rota, m_transform.angle.x);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Rota);

	D3DXMatrixRotationY(&Rota, m_transform.angle.y);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Rota);

	D3DXMatrixRotationZ(&Rota, m_transform.angle.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Rota);

	Rota = mWorld;

	D3DXMatrixTranslation(&Trans, m_transform.position.x, m_transform.position.y, m_transform.position.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Trans);

//
//	// もとのレンダリングターゲットを保存
//	IDirect3DSurface9* pOldBackBuffer;
//	IDirect3DSurface9* pOldZBuffer;
//
//	(*graphicsDevice()).GetRenderTarget(0, &pOldBackBuffer);
//	(*graphicsDevice()).GetDepthStencilSurface(&pOldZBuffer);
//
//	// レンダリングターゲットの変更
//	(*graphicsDevice()).SetRenderTarget(0, m_pOriginalSurf);
//	(*graphicsDevice()).SetDepthStencilSurface(m_pMapZ);
//
//	(*graphicsDevice()).Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
//
//	// オフスクリーンレンダリング
////m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ShadowMap.hlsl"));	// 使用するshaderファイルをシャドウマップ用に変更
//	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ModelShader.hlsl"));	// 使用するshaderファイルをシャドウマップ用に変更
//
//	SetUpTechnique();
//	//m_pEffect->SetTechnique("ShadowMapping");
//	if (m_pEffect == nullptr){
//		m_pEffect->SetTechnique("BasicTec");
//	}
//	m_pEffect->Begin(NULL, 0);
//	m_pEffect->BeginPass(0);
//	//m_pEffect->SetTexture("g_ShadowMap", m_pShadow);
//	SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);
//	m_pEffect->SetMatrix("World"/*エフェクトファイル内の変数名*/, &mWorld/*設定したい行列へのポインタ*/);
//	// 頂点フォーマットをセット
//	(*graphicsDevice()).SetFVF(m_pMesh->GetFVF());
//
//	
//	for (DWORD i = 0; i < m_NumMaterials; i++){
//		m_pEffect->SetTexture("g_Texture", m_pMeshTex[i]);	// テクスチャ情報をセット
//		m_pEffect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。
//		m_pMesh->DrawSubset(i);						// メッシュを描画
//	}
//	m_pEffect->EndPass();
//	m_pEffect->End();
//	// レンダリングターゲットを元に戻す
//	(*graphicsDevice()).SetRenderTarget(0, pOldBackBuffer);
//	(*graphicsDevice()).SetDepthStencilSurface(pOldZBuffer);
//	//pOldBackBuffer->Release();
//	//pOldZBuffer->Release();
//	

	// 通常描画
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ModelShader.hlsl"));	// 使用するshaderファイルを指定(デフォルト)
	SetUpTechnique();
	if (m_pMeshTex[0] == nullptr){
		m_pEffect->SetTechnique("BasicTec");
	}

	UINT numPass;
	m_pEffect->Begin(&numPass/*テクニック内に定義されているパスの数が返却される*/, 0);
	m_pEffect->BeginPass(0);	//パスの番号を指定してどのパスを使用するか指定

	// 現在のプロジェクション行列とビュー行列をシェーダーに転送
	SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);

	// ディフューズライトの向きをシェーダーに転送
	m_pEffect->SetVectorArray("diffuseLightDirection", m_light.GetDiffuseLightDirection(), NUM_DIFFUSE_LIGHT);
	// ディフューズライトのカラーをシェーダーに転送
	m_pEffect->SetVectorArray("diffuseLightColor", m_light.GetDiffuseLightColor(), NUM_DIFFUSE_LIGHT);
	// 環境光をシェーダーに転送
	m_pEffect->SetVector("ambientLight", &m_light.GetAmbientLight());
	// 視点をシェーダーに転送
	m_pEffect->SetVector("EyePosition", reinterpret_cast<D3DXVECTOR4*>(&SINSTANCE(CRenderContext)->GetCurrentCamera()->GetPos()));

	//ここで固定描画と同じように、ローカル座標に設定された頂点群をデバイスに渡す。通常と同じ方法。
	//	メッシュも同じく、マテリアルやテクスチャを設定
	//DrawSubset()を呼び出して描画

	// ワールドトランスフォーム(絶対座標変換)
	// ワールド行列生成


	m_pEffect->SetMatrix("Rota", &Rota);
	m_pEffect->SetMatrix("World"/*エフェクトファイル内の変数名*/, &mWorld/*設定したい行列へのポインタ*/);

	// 頂点フォーマットをセット
	(*graphicsDevice()).SetFVF(m_pMesh->GetFVF());

	for (DWORD i = 0; i < m_NumMaterials; i++){
		//m_pEffect->SetTexture("g_Texture", m_pShadow);	// テクスチャ情報をセット
		m_pEffect->SetTexture("g_Texture", m_pMeshTex[i]);	// テクスチャ情報をセット
		m_pEffect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。
		m_pMesh->DrawSubset(i);						// メッシュを描画
	}
	m_pEffect->EndPass();
	m_pEffect->End();
}