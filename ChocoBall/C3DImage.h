#pragma once
#include "stdafx.h"
#include "Graphicsdevice.h"
#include "GameObject.h"
#include "Light.h"

class C3DImage :public CGameObject{
public:
	C3DImage(){};
	~C3DImage(){};
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void SetUpTechnique()override{
		m_pEffect->SetTechnique("TextureTec");
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
private:
	IMAGE3D* m_pImage;
	D3DXMATRIX m_Rota;	// 回転行列
protected:
	D3DXMATRIX m_World;		// ワールド行列
	CLight m_light;
	D3DXVECTOR3 m_lightDir[NUM_DIFFUSE_LIGHT];
	short count;
	D3DXVECTOR3 dir;
};
