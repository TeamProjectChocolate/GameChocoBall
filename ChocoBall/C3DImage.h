#pragma once
#include "stdafx.h"
#include "Graphicsdevice.h"
#include "GameObject.h"
#include "Light.h"

class C3DImage :public CGameObject{
public:
	C3DImage(){ /*m_pMapZ = nullptr; m_pShadow = nullptr; m_pOriginalSurf = nullptr;*/ };
	~C3DImage(){};
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void SetUpTechnique()override{
		m_pEffect->SetTechnique("TextureTec");
	}
	HRESULT SetImage();
	HRESULT ReSet();
	HRESULT LoadXFile();
private:
	D3DMATERIAL9* m_pMeshMat;			// マテリアル情報
	LPDIRECT3DTEXTURE9* m_pMeshTex;		// メッシュのテクスチャ
	LPD3DXBUFFER m_pMaterials;
	DWORD m_NumMaterials;
	LPD3DXMESH m_pMesh;

	//LPDIRECT3DSURFACE9 m_pMapZ;			// 深度バッファ
	//LPDIRECT3DTEXTURE9 m_pShadow;		// 影を落とすためのテクスチャ
	//LPDIRECT3DSURFACE9 m_pOriginalSurf;	// サーフェス
protected:
	D3DXMATRIX mWorld;		// ワールド行列
	CLight m_light;
	D3DXVECTOR3 m_lightDir[NUM_DIFFUSE_LIGHT];
	short count;
	D3DXVECTOR3 dir;
};
