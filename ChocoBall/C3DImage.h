#pragma once
#include "stdafx.h"
#include "Graphicsdevice.h"
#include "GameObject.h"
#include "SkinModelData.h"

extern UINT g_NumBoneMatricesMax;
extern D3DXMATRIXA16* g_pBoneMatrices;

const float	g_cTurnSpeed = D3DXToRadian(10.0f);

class C3DImage :public CGameObject{
public:
	C3DImage(){
		m_pImage = nullptr;
		m_pSkinModel = nullptr;
	};
	~C3DImage(){};
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void SetUpTechnique()override{
		m_pEffect->SetTechnique("NotNormalMapTextureTec");
	}
	IMAGE3D* GetImage(){
		return m_pImage;
	}
	D3DXMATRIX& GetWorldMatrix(){
		return m_World;
	}
	HRESULT SetImage();
	HRESULT ReSet();
	HRESULT LoadXFile();
	void SetRotation(D3DXVECTOR3 axis, float rota){
		D3DXQuaternionRotationAxis(&m_transform.angle, &axis, rota);
	}
private:
	IMAGE3D* m_pImage;
	D3DXMATRIX m_Rota;	// 回転行列
	void UpdateFrame(LPDIRECT3DDEVICE9, LPD3DXFRAME);
	void AnimationUpdate();
	void NonAnimationUpdate();
	void DrawFrame(LPDIRECT3DDEVICE9, LPD3DXFRAME);
	void DrawMeshContainer(LPDIRECT3DDEVICE9, LPD3DXMESHCONTAINER, LPD3DXFRAME);
	void AnimationDraw(LPDIRECT3DDEVICE9, D3DXMESHCONTAINER_DERIVED*, LPD3DXMESHCONTAINER, LPD3DXFRAME);
	void NonAnimationDraw();
protected:
	D3DXMATRIX m_World;		// ワールド行列
	CSkinModelData* m_pSkinModel;
};
