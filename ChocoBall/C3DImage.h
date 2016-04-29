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
	D3DMATERIAL9* m_pMeshMat;			// �}�e���A�����
	LPDIRECT3DTEXTURE9* m_pMeshTex;		// ���b�V���̃e�N�X�`��
	LPD3DXBUFFER m_pMaterials;
	DWORD m_NumMaterials;
	LPD3DXMESH m_pMesh;

	//LPDIRECT3DSURFACE9 m_pMapZ;			// �[�x�o�b�t�@
	//LPDIRECT3DTEXTURE9 m_pShadow;		// �e�𗎂Ƃ����߂̃e�N�X�`��
	//LPDIRECT3DSURFACE9 m_pOriginalSurf;	// �T�[�t�F�X
protected:
	D3DXMATRIX mWorld;		// ���[���h�s��
	CLight m_light;
	D3DXVECTOR3 m_lightDir[NUM_DIFFUSE_LIGHT];
	short count;
	D3DXVECTOR3 dir;
};
