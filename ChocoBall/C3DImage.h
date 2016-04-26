#pragma once
#include "stdafx.h"
#include "Graphicsdevice.h"
#include "GameObject.h"

class C3DImage :public CGameObject{
public:
	C3DImage(){};
	~C3DImage(){};
	virtual void Initialize()override;
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
	LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
protected:
	D3DXMATRIX mWorld;		// ���[���h�s��
};
