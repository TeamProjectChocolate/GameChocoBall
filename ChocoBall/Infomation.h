#pragma once

class CGameObject;
class CSkinModelData;

#define MAX_FILENAME 255

#define NUM_DIFFUSE_LIGHT 4		// �g�p����f�B�t���[�Y���C�g�̐�

#define MAX_PRIORTY 255

enum PRIORTY{CONFIG = 0,PLAYER,OBJECT3D,OBJECT3D_ALPHA,OBJECT2D,OBJECT2D_ALPHA,LOWEST = MAX_PRIORTY};

enum GAMEEND_ID{ CONTINUE = 0,CLEAR, OVER };

// �V�F�[�_�t�@�C���i�[�p�\����
typedef struct EFFECT_DATA{
	CHAR pFileName[MAX_FILENAME + 1];
	LPD3DXEFFECT Effect;	// �C���^�t�F�[�X�|�C���^
}EFFECT_DATA;

// 3D���f�����i�[�p�\����
typedef struct IMAGE3D{
	CHAR pFileName[MAX_FILENAME + 1];
	CSkinModelData* pModel;
}IMAGE3D;

// 2D�摜�̑傫���i�[�p�\����
typedef struct TEXTURE_SIZE{
	float x;
	float y;
};

// 2D���f�����i�[�p�\����
typedef struct IMAGE2D{
	CHAR pFileName[MAX_FILENAME + 1];
	LPDIRECT3DTEXTURE9 pTex;
	TEXTURE_SIZE RealSize;
	TEXTURE_SIZE UnRealSize;
}IMAGE2D;


// �I�u�W�F�N�g���W�i�[�\����
typedef struct TRANSEFORM{
	D3DXVECTOR3 position;
	D3DXQUATERNION angle;
	D3DXVECTOR3 scale;
}TRANSFORM;

// �A�j���[�V�����p�s��
typedef struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//�����ςݍs��B
};

// �A�j���[�V����3D���f�����i�[�p�\����
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

enum STAGE_ID{ FIRST = 0,MAX,STAGE_NONE = 999};

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540