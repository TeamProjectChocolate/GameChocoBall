#pragma once
#include "stdafx.h"
#include "Graphicsdevice.h"
#include "GameObject.h"

class C3DImage :public CGameObject{
public:
	C3DImage(){ m_ObjecType = OBJECT::TYPE_3D; };
	~C3DImage(){};
	virtual void Draw()override;
	HRESULT SetImage();
	HRESULT ReSet();
	HRESULT LoadXFile();
	virtual void SetUp();
private:
	D3DMATERIAL9* m_pMeshMat;			// マテリアル情報
	LPDIRECT3DTEXTURE9* m_pMeshTex;		// メッシュのテクスチャ
	LPD3DXBUFFER m_pMaterials;
	DWORD m_NumMaterials;
	LPD3DXMESH m_pMesh;
	LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
protected:
	D3DXMATRIX mWorld;		// ワールド行列
	D3DXMATRIX m_translation;
	D3DXMATRIX m_rotation;
};
