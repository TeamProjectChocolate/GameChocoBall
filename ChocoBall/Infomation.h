#pragma once

class CGameObject;
class CSkinModelData;

#define MAX_FILENAME 255

#define NUM_DIFFUSE_LIGHT 4		// 使用するディフューズライトの数

#define MAX_PRIORTY 255
enum PRIORTY{CONFIG = 0,PLAYER,OBJECT3D,OBJECT2D,LOWEST = MAX_PRIORTY};

// シェーダファイル格納用構造体
typedef struct EFFECT_DATA{
	CHAR pFileName[MAX_FILENAME + 1];
	LPD3DXEFFECT Effect;	// インタフェースポインタ
}EFFECT_DATA;

// 3Dモデル情報格納用構造体
typedef struct IMAGE3D{
	CHAR pFileName[MAX_FILENAME + 1];
	CSkinModelData* pModel;
	//D3DMATERIAL9* pMat;
	//LPDIRECT3DTEXTURE9* ppTex;
	//LPD3DXMESH pMesh;
	//DWORD NumMaterials;
}IMAGE3D;

// 2Dモデル情報格納用構造体
typedef struct IMAGE2D{
	CHAR pFileName[MAX_FILENAME + 1];
	LPDIRECT3DTEXTURE9 pTex;
	RECT rect;
}IMAGE2D;


// オブジェクト座標格納構造体
typedef struct TRANSEFORM{
	D3DXVECTOR3 position;
	D3DXQUATERNION angle;
	D3DXVECTOR3 scale;
}TRANSFORM;

// アニメーション用行列
typedef struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//合成済み行列。
};

// アニメーション3Dモデル情報格納用構造体
typedef struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
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

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540