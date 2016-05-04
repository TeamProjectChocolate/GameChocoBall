#include "stdafx.h"
#include "C3DImage.h"
#include "Effect.h"
#include "ImageManager.h"
#include "RenderContext.h"
#include "Camera.h"
#include "GraphicsDevice.h"
#include "ShadowRender.h"

HRESULT C3DImage::SetImage(){

	m_pImage = SINSTANCE(CImageManager)->Find3DImage(m_pFileName);
	if (m_pImage != nullptr){
		return S_OK;
	}

	LoadXFile();
	return S_OK;
}

HRESULT C3DImage::LoadXFile(){
	DWORD i;
	LPD3DXBUFFER pMaterials;
	DWORD NumMaterials;
	LPD3DXMESH pMesh;

	// Xファイルロード
	if (FAILED(D3DXLoadMeshFromX(m_pFileName, D3DXMESH_MANAGED, graphicsDevice(), NULL, &pMaterials, NULL, &NumMaterials, &pMesh))){		// Xファイル読み取り
		return E_FAIL;
	};

	// Xファイルに法線がない場合は、法線を書き込む
	if (!(pMesh->GetFVF() & D3DFVF_NORMAL)){
		ID3DXMesh* pTempMesh = NULL;
		pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF() | D3DFVF_NORMAL, graphicsDevice(), &pTempMesh);
		D3DXComputeNormals(pTempMesh, NULL);
		pMesh->Release();
		pMesh = pTempMesh;
	}
	// 頂点宣言
	const D3DVERTEXELEMENT9 vertexDecl[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		{ 0, 20, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
		{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 }, 
		{ 0, 56, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		D3DDECL_END()
	};

	LPD3DXMESH pCloneMesh = nullptr;

	pMesh->CloneMesh(pMesh->GetOptions(), vertexDecl, &(*graphicsDevice()), &pCloneMesh);
	D3DXComputeTangentFrameEx(pCloneMesh,
		D3DDECLUSAGE_TEXCOORD,
		0,
		D3DDECLUSAGE_TANGENT,
		0,
		D3DDECLUSAGE_BINORMAL,
		0,
		D3DDECLUSAGE_NORMAL,
		0,
		0,
		NULL,
		0.01f,    //ボケ具合.値をおおきくするとぼけなくなる
		0.25f,
		0.01f,
		&pCloneMesh,
		NULL
		);

	pMesh->Release();
	pMesh = pCloneMesh;

	// マテリアル、テクスチャの準備
	D3DMATERIAL9* pMeshMat = new D3DMATERIAL9[NumMaterials];		// メッシュ情報を確保
	LPDIRECT3DTEXTURE9* pMeshTex = new LPDIRECT3DTEXTURE9[NumMaterials];		// テクスチャを確保

	D3DXMATERIAL* d3Mat = (D3DXMATERIAL*)pMaterials->GetBufferPointer();

	for (i = 0; i < NumMaterials; i++){
		pMeshMat[i] = d3Mat[i].MatD3D;		// マテリアル情報セット
		pMeshMat[i].Ambient = pMeshMat[i].Diffuse;		// 環境光初期化

		pMeshTex[i] = NULL;		// テクスチャ初期化
		if (d3Mat[i].pTextureFilename != NULL && lstrlen(d3Mat[i].pTextureFilename) > 0){		// 使用しているテクスチャがあれば読み込む

			if (FAILED(D3DXCreateTextureFromFile(graphicsDevice(), d3Mat[i].pTextureFilename, &pMeshTex[i]))){
				return E_FAIL;
			}
		}
	}

	SINSTANCE(CImageManager)->Add3D(m_pFileName, pMeshMat, pMeshTex, NumMaterials, pMesh);		// IMAGE情報配列に追加
	m_pImage = new IMAGE3D;
	m_pImage->NumMaterials = NumMaterials;
	m_pImage->pMat = pMeshMat;
	m_pImage->pMesh = pMesh;
	m_pImage->ppTex = pMeshTex;

	pMaterials->Release();		// マテリアル情報解放
	return S_OK;
}

void C3DImage::Initialize(){
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/ModelShader.hlsl"));	// 使用するshaderファイルを指定(デフォルト)

	m_lightDir[0] = D3DXVECTOR3(0.707f, 0.707f, 0.0f);
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


	D3DXMATRIX Trans;	// 移動行列
	D3DXMATRIX Scale;	// 拡大・縮小行列

	D3DXMatrixIdentity(&m_World);	// 行列初期化

	D3DXMatrixRotationX(&m_Rota, m_transform.angle.x);
	D3DXMatrixMultiply(&m_World, &m_World, &m_Rota);

	D3DXMatrixRotationY(&m_Rota, m_transform.angle.y);
	D3DXMatrixMultiply(&m_World, &m_World, &m_Rota);

	D3DXMatrixRotationZ(&m_Rota, m_transform.angle.z);
	D3DXMatrixMultiply(&m_World, &m_World, &m_Rota);

	m_Rota = m_World;

	D3DXMatrixScaling(&Scale, m_transform.scale.x, m_transform.scale.y, m_transform.scale.z);
	D3DXMatrixMultiply(&m_World, &m_World, &Scale);

	D3DXMatrixTranslation(&Trans, m_transform.position.x, m_transform.position.y, m_transform.position.z);
	D3DXMatrixMultiply(&m_World, &m_World, &Trans);

}

void C3DImage::Draw(){

	if (m_pImage->ppTex[0] == nullptr){
		m_pEffect->SetTechnique("NotNormalMapBasicTec");
	}

	UINT numPass;
	m_pEffect->Begin(&numPass/*テクニック内に定義されているパスの数が返却される*/, 0);
	m_pEffect->BeginPass(0);	//パスの番号を指定してどのパスを使用するか指定

	// 透明度有効化
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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

	SINSTANCE(CShadowRender)->SetShadowCamera(m_pEffect);
	//ここで固定描画と同じように、ローカル座標に設定された頂点群をデバイスに渡す。通常と同じ方法。
	//	メッシュも同じく、マテリアルやテクスチャを設定
	//DrawSubset()を呼び出して描画

	// ワールドトランスフォーム(絶対座標変換)
	// ワールド行列生成


	m_pEffect->SetMatrix("Rota", &m_Rota);
	m_pEffect->SetMatrix("World"/*エフェクトファイル内の変数名*/, &m_World/*設定したい行列へのポインタ*/);

	m_pEffect->SetFloat("Alpha", GetAlpha());

	// 頂点フォーマットをセット
	(*graphicsDevice()).SetFVF(m_pImage->pMesh->GetFVF());

	for (DWORD i = 0; i < m_pImage->NumMaterials; i++){
		m_pEffect->SetTexture("g_ShadowMap", SINSTANCE(CShadowRender)->GetTexture());	// テクスチャ情報をセット
		m_pEffect->SetTexture("g_Texture", m_pImage->ppTex[i]);	// テクスチャ情報をセット
		m_pEffect->SetTexture("g_normalMap", SINSTANCE(CImageManager)->Find2DImage(_T("image/normal.jpg"))->pTex);
		m_pEffect->CommitChanges();						//この関数を呼び出すことで、データの転送が確定する。
		m_pImage->pMesh->DrawSubset(i);						// メッシュを描画
	}
	m_pEffect->EndPass();
	m_pEffect->End();
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}