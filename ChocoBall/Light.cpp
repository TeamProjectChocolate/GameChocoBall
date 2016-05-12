#include "stdafx.h"
#include "Light.h"


void CLight::SetLight(LPD3DXEFFECT pEffect){
	// �f�B�t���[�Y���C�g�̌������V�F�[�_�[�ɓ]��
	pEffect->SetVectorArray("diffuseLightDirection", m_diffuseLightDirection, NUM_DIFFUSE_LIGHT);
	// �f�B�t���[�Y���C�g�̃J���[���V�F�[�_�[�ɓ]��
	pEffect->SetVectorArray("diffuseLightColor", m_diffuseLightColor, NUM_DIFFUSE_LIGHT);
	// �������V�F�[�_�[�ɓ]��
	pEffect->SetVector("ambientLight", &m_ambientLight);
}
