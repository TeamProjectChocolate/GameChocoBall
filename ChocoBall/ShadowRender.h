#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "Camera.h"

class CShadowRender
{
	SINGLETON_DECL(CShadowRender)
public:
	void Entry(C3DImage*);
	void Initialize();
	void Update();
	void Draw();
	void SetObjectPos(D3DXVECTOR3 pos){
		m_target = pos;
	}
	void SetShadowCameraPos(D3DXVECTOR3 pos){
		m_ShadowLightPos = pos;
	}
	void SetShadowCameraDir(D3DXVECTOR3 dir){
		m_ShadowLightDirection = dir;
	}
	LPDIRECT3DTEXTURE9 GetTexture(){
		return m_pShadow;
	}
	void SetShadowCamera(LPD3DXEFFECT effect){
		effect->SetMatrix("LightViewProj", &(m_camera.GetView() * m_camera.GetProj()));
	}
private:
	LPDIRECT3DSURFACE9 m_pMapZ;			// �[�x�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pShadow;		// �e�𗎂Ƃ����߂̃e�N�X�`��
	LPDIRECT3DSURFACE9 m_pOriginalSurf;	// �T�[�t�F�X
	LPD3DXEFFECT m_pEffect;
	vector<C3DImage*> m_ShadowObjects;	// �e�𐶐��������I�u�W�F�N�g�̔z��
	D3DXVECTOR3 m_target;		// �e�𐶐��������I�u�W�F�N�g�̃|�W�V����
	D3DXVECTOR3 m_ShadowLightPos;		// �e��`�悷�邽�߂̃J�����̃|�W�V����
	D3DXVECTOR3 m_ShadowLightDirection;		// �e��`�悷�邽�߂̃J�����̌���
	CCamera m_camera;
	D3DXMATRIX m_View;					// ���C�g�̃r���[�s��
	D3DXMATRIX m_Proj;					// ���C�g�̃v���W�F�N�V�����s��
	void DeleteAll();
};

