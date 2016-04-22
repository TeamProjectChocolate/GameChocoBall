#include "C3DImage.h"
#include "Effect.h"
#include "ImageManager.h"


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

void C3DImage::SetUp(){
	// ワールドトランスフォーム(絶対座標変換)
	D3DXMatrixIdentity(&mWorld);	// 行列初期化

	D3DXMatrixRotationX(&m_rotation, m_transform.angle.x);
	D3DXMatrixMultiply(&mWorld, &mWorld, &m_rotation);

	D3DXMatrixRotationY(&m_rotation, m_transform.angle.y);
	D3DXMatrixMultiply(&mWorld, &mWorld, &m_rotation);

	D3DXMatrixRotationZ(&m_rotation, m_transform.angle.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &m_rotation);

	D3DXMatrixTranslation(&m_translation, m_transform.position.x, m_transform.position.y, m_transform.position.z/*-18.0f*/);
	D3DXMatrixMultiply(&mWorld, &mWorld, &m_translation);

	SINSTANCE(CEffect)->GetEffect()->SetMatrix("World"/*エフェクトファイル内の変数名*/, &mWorld/*設定したい行列へのポインタ*/);
	//g_pEffect->SetTexture("g_Texture", texture /*テクスチャ情報*/);
	SINSTANCE(CEffect)->GetEffect()->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
}

void C3DImage::Draw(){

	DWORD i;

	// 頂点シェーダをセット(使わない場合はNULL)
	//(*graphicsDevice()).SetVertexShader(NULL);

	this->SetUp();

	// 頂点フォーマットをセット
	(*graphicsDevice()).SetFVF(m_pMesh->GetFVF());

	for (i = 0; i < m_NumMaterials; i++){
		//(*graphicsDevice()).SetMaterial(&m_pMeshMat[i]);		// マテリアル情報をセット
		SINSTANCE(CEffect)->GetEffect()->SetTexture("g_Texture", m_pMeshTex[i]);	// テクスチャ情報をセット
		m_pMesh->DrawSubset(i);						// メッシュを描画
	}
}