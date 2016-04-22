#pragma once

class CGameObject;

enum OBJECT{TYPE_2D = 0,TYPE_3D};

// �V�F�[�_�t�@�C���i�[�p�\����
typedef struct EFFECT_DATA{
	LPCSTR pFileName;
	LPD3DXEFFECT Effect;	// �C���^�t�F�[�X�|�C���^
}EFFECT_DATA;

// 3D���f�����i�[�p�\����
typedef struct IMAGE3D{
	LPCSTR pFileName;
	D3DMATERIAL9* pMat;
	LPDIRECT3DTEXTURE9* ppTex;
	LPD3DXMESH pMesh;
	DWORD NumMaterials;
}IMAGE3D;

// 2D���f�����i�[�p�\����
typedef struct IMAGE2D{
	LPCSTR pFileName;
	LPDIRECT3DTEXTURE9 pTex;
	RECT rect;
}IMAGE2D;


// �I�u�W�F�N�g���W�i�[�\����
typedef struct TRANSEFORM{
	D3DXVECTOR3 position;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
}TRANSFORM;
