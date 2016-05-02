#pragma once

class CGameObject;

#define MAX_FILENAME 255

#define NUM_DIFFUSE_LIGHT 4		// 使用するディフューズライトの数


// シェーダファイル格納用構造体
typedef struct EFFECT_DATA{
	CHAR pFileName[MAX_FILENAME];
	LPD3DXEFFECT Effect;	// インタフェースポインタ
}EFFECT_DATA;

// 3Dモデル情報格納用構造体
typedef struct IMAGE3D{
	LPCSTR pFileName;
	D3DMATERIAL9* pMat;
	LPDIRECT3DTEXTURE9* ppTex;
	LPD3DXMESH pMesh;
	DWORD NumMaterials;
}IMAGE3D;

// 2Dモデル情報格納用構造体
typedef struct IMAGE2D{
	LPCSTR pFileName;
	LPDIRECT3DTEXTURE9 pTex;
	RECT rect;
}IMAGE2D;


// オブジェクト座標格納構造体
typedef struct TRANSEFORM{
	D3DXVECTOR3 position;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
}TRANSFORM;


#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540