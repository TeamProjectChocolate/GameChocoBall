#pragma once
#include "stdafx.h"
#include "Graphicsdevice.h"
#include "GameObject.h"
#include "Light.h"

const float	g_cTurnSpeed = D3DXToRadian(10.0f);
static const float fPI = 3.14159265358979323846f;


class C3DImage :public CGameObject{
public:
	C3DImage(){
		m_pImage = nullptr;
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
protected:
	D3DXMATRIX m_World;		// ワールド行列
	CLight m_light;
	D3DXVECTOR3 m_lightDir[NUM_DIFFUSE_LIGHT];
	short count;
	D3DXVECTOR3 dir;
};
