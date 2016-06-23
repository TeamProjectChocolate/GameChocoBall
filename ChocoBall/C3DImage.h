#pragma once
#include "stdafx.h"
#include "Graphicsdevice.h"
#include "GameObject.h"
#include "SkinModelData.h"
#include "Animation.h"

extern UINT g_NumBoneMatricesMax;
extern D3DXMATRIXA16* g_pBoneMatrices;

class C3DImage :public CGameObject{
public:
	C3DImage(){
		m_pImage = nullptr;
		m_UseBorn = false;
	};
	~C3DImage(){};
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void SetUpTechniqueAnimation(){
		m_pEffect->SetTechnique("NotNormalMapAnimationFresnelTec");
	}
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
	void DrawFrame(LPD3DXFRAME);
	void DrawMeshContainer(LPD3DXMESHCONTAINER, LPD3DXFRAME);
	void AnimationDraw(D3DXMESHCONTAINER_DERIVED*,D3DXFRAME_DERIVED*);
	void NonAnimationDraw(D3DXFRAME_DERIVED*);
protected:
	// 3D描画用メンバ変数
	D3DXMATRIX m_World;		// ワールド行列
	CAnimation m_animation;
	int m_currentAnimNo;
	bool m_UseBorn;		// ボーンを使用するかどうかのフラグ(trueなら使用、falseなら使用しない)
};
