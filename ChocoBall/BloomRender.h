#pragma once
#include "stdafx.h"
#include "Effect.h"
#include "Primitive.h"

//#define USE_LOW_QUALITY_BLOOM		//��`�Œ�N�H���e�B�̃u���[���������L���ɂȂ�B�i���͗򉻂���B

typedef struct int2{
	int w;
	int h;
};

class CBloomRender
{
public:
	CBloomRender();
	~CBloomRender();
	/*!
	* @brief	�`��B
	*/
	void Draw();
	/*!
	* @brief	�쐬�B
	*/
	void Create();

	LPDIRECT3DTEXTURE9 GetTexture(){
		return m_pluminanceTexture;
	}
private:
	/*!
	* @brief	�K�E�X�t�B���^�̏d�݂��X�V�B
	*/
	void UpdateWeight(float dispersion);
private:
#if defined(USE_LOW_QUALITY_BLOOM)
	static const int NUM_WEIGHTS = 4;
#else
	static const int NUM_WEIGHTS = 8;
#endif
	LPD3DXEFFECT	m_pEffect;						//!<�G�t�F�N�g�B
	LPDIRECT3DSURFACE9	m_luminanceRenderTarget;		//!<�P�x�𒊏o���郌���_�����O�^�[�Q�b�g�B
	LPDIRECT3DSURFACE9	m_downSamplingRenderTarget[4];	//!<�P�x���_�E���T���v�����O���邽�߂̃����_�����O�^�[�Q�b�g�B
	LPDIRECT3DTEXTURE9 m_pluminanceTexture;
	LPDIRECT3DTEXTURE9 m_pTexture[4];
	bool			m_isEnable;						//!<�L���H
	float				m_weights[NUM_WEIGHTS];
	CPrimitive* m_Primitive;
	int2 m_size[4];
};

