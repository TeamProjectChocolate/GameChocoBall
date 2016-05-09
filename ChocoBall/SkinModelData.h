#pragma once

#include "stdafx.h"

struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//合成済み行列。
};
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
	LPDIRECT3DTEXTURE9* ppTextures;
	LPD3DXMESH pOrigMesh;
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD NumAttributeGroups;
	DWORD NumInfl;
	LPD3DXBUFFER pBoneCombinationBuf;
	D3DXMATRIX** ppBoneMatrixPtrs;
	D3DXMATRIX* pBoneOffsetMatrices;
	DWORD NumPaletteEntries;
	bool UseSoftwareVP;
	DWORD iAttributeSW;
};

class CSkinModelData
{
public:
	CSkinModelData();
	~CSkinModelData();
	void LoadModelData(LPCSTR);
	void SetUpBoneMatrixPointers(LPD3DXFRAME, LPD3DXFRAME);
	void SetUpBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER,LPD3DXFRAME);
	LPD3DXFRAME GetFrameRoot()
	{
		return m_frameRoot;
	}
	ID3DXAnimationController* GetAnimationController()
	{
		return m_pAnimController;
	}
	void UpdateBoneMatrix(const D3DXMATRIX* matWorld);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, const D3DXMATRIX* pParentMatrix);
private:
	LPD3DXFRAME m_frameRoot;		// フレームルート
	ID3DXAnimationController* m_pAnimController;	// アニメーションコントローラ
};

