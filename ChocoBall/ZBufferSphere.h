#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Light.h"

class CGameCamera;

class CPlayer;

class CZBufferSphere : public C3DImage{
public:
	CZBufferSphere();
	~CZBufferSphere();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void DrawDepth(LPD3DXEFFECT,const D3DXVECTOR2&)override;
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("ZMask");
	};
	LPDIRECT3DTEXTURE9 GetTexture(){
		return m_pZBufferSphereShadow;
	}
private:
	CGameCamera* GameCamera;
	CPlayer* Player;
	LPDIRECT3DSURFACE9 m_pMapZ = nullptr;			// �[�x�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pZBufferSphereShadow = nullptr;		// �e�𗎂Ƃ����߂̃e�N�X�`��
	LPDIRECT3DSURFACE9 m_pOriginalSurf = nullptr;	// �T�[�t�F�X
};