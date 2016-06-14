#pragma once

#include "stdafx.h"
#include "Light.h"
#include "Primitive.h"

class CCamera;

class CRenderContext{
	SINGLETON_DECL(CRenderContext)
public:
	void CreateRenderingTerget();
	void RenderingStart();
	void RenderingEnd();
	void SetRenderingBuffer();

	void SetCurrentCamera(CCamera* cam)
	{
		m_pCamera = cam;
	}
	CCamera* GetCurrentCamera()
	{
		return m_pCamera;
	}
	void SetCurrentLight(CLight* light){
		m_pLight = light;
	}
	CLight* GetCurrentLight(){
		return m_pLight;
	}
private:
	LPDIRECT3DSURFACE9 m_pMapZ = nullptr;		// �[�x�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;		// �o�b�t�@�ɃR�s�[���邽�߂̃e�N�X�`��
	LPDIRECT3DSURFACE9 m_pOriginalSurf = nullptr;	// �T�[�t�F�X
	LPDIRECT3DSURFACE9 m_SavedMapZ;			// �[�x�o�b�t�@��ۑ����Ă������߂̕ϐ�
	LPDIRECT3DSURFACE9 m_SavedBuffer;			// �o�b�t�@��ۑ����Ă������߂̕ϐ�
	CPrimitive m_copyBackBufferPrim;		//!<���C�������_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɃR�s�[����Ƃ��Ɏg���v���~�e�B�u�B
	LPD3DXEFFECT m_pEffect;
	unsigned int m_bufferSize_Width;
	unsigned int m_bufferSize_Height;
	CCamera* m_pCamera = nullptr;
	CLight* m_pLight = nullptr;
	void DeleteAll(){};
};
