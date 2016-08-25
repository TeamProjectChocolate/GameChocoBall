#pragma once
#include "stdafx.h"
#include "Effect.h"
#include "Primitive.h"


class CDofRender
{
public:
	CDofRender();
	~CDofRender();
	/*!
	* @brief	�`��B
	*/
	void Draw(LPDIRECT3DTEXTURE9);
	/*!
	* @brief	�쐬�B
	*/
	void Create();
	LPDIRECT3DTEXTURE9 GetDepthTex(){
		return m_pDepthSamplingTexture;
	}
private:
	/*!
	* @brief	�K�E�X�t�B���^�̏d�݂��X�V�B
	*/
	void UpdateWeight(float dispersion);
private:
	static const int NUM_WEIGHTS = 8;
	LPD3DXEFFECT	m_pEffect;						//!<�G�t�F�N�g�B
	LPDIRECT3DSURFACE9 m_DepthSamplingTarget;	// �[�x��񒊏o�p�����_�����O�^�[�Q�b�g
	LPDIRECT3DTEXTURE9 m_pDepthSamplingTexture;	// �[�x�����������ރe�N�X�`��
	LPDIRECT3DSURFACE9	m_RenderTarget[2];	//!<�ڂ������߂̃����_�����O�^�[�Q�b�g�B
	LPDIRECT3DTEXTURE9 m_pBlurTexture[2];	// �ڂ������e�N�X�`��(X�����̂ڂ�����Y�����̂ڂ����œ��)
	bool			m_isEnable;						//!<�L���H
	float				m_weights[NUM_WEIGHTS];
	CPrimitive* m_Primitive;
	D3DXVECTOR2 m_FarNear;
};

