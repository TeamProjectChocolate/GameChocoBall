#include "C3DImage.h"
#include "Effect.h"
#include "ImageManager.h"
#include "RenderContext.h"
#include "Camera.h"

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
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/Effect00.hlsl"));	// 使用するshaderファイルを指定(デフォルト)
}

void C3DImage::Draw(){
	SetUpTechnique();
	if (m_pMeshTex[0] == nullptr){
		m_pEffect->SetTechnique("BasicTec");
	}

	UINT numPass;
	m_pEffect->Begin(&numPass/*テクニック内に定義されているパスの数が返却される*/, 0);
	m_pEffect->BeginPass(0);	//パスの番号を指定してどのパスを使用するか指定

	SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);
	//ここで固定描画と同じように、ローカル座標に設定された頂点群をデバイスに渡す。通常と同じ方法。
	//	メッシュも同じく、マテリアルやテクスチャを設定
	//DrawSubset()を呼び出して描画

	// ワールドトランスフォーム(絶対座標変換)
	// ワールド行列生成

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

	D3DXMatrixTranslation(&Trans, m_transform.position.x, m_transform.position.y, m_transform.position.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Trans);

	m_pEffect->SetMatrix("World"/*エフェクトファイル内の変数名*/, &mWorld/*設定したい行列へのポインタ*/);

	// 頂点フォーマットをセット
	(*graphicsDevice()).SetFVF(m_pMesh->GetFVF());

	DWORD i;

	for (i = 0; i < m_NumMaterials; i++){
		m_pEffect->SetTexture("g_Texture", m_pMeshTex[i]);	// テクスチャ情報をセット
		m_pEffect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
		m_pMesh->DrawSubset(i);						// メッシュを描画
	}
	m_pEffect->EndPass();
	m_pEffect->End();
}