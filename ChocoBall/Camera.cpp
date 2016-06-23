#include "stdafx.h"
#include "Camera.h"
#include "GraphicsDevice.h"
#include "Effect.h"
#include "BulletPhysics.h"

CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}

void CCamera::Initialize(){
	m_position.x = 0.0f;
	m_position.y = 1.2f;
	m_position.z = -20.0f;
	m_target.x = 0.0f;
	m_target.y = 0.1f;
	m_target.z = 0.0f;
	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;
	m_ViewAngle = D3DXToRadian(45);		// 45�x�����W�A���ɕϊ����Ċi�[
	m_aspect = 1.0f / 1.0f;				// �A�X�y�N�g��Ɍv�Z
	m_Near = 1.0f;						// �ǂ�����
	m_Far = 1000.0f;					// �ǂ��܂ŕ`�悷�邩
	m_updateType = enUpdateTypeTarget;
	m_Axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

void CCamera::Update(){
	// �ˉe�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&m_Proj);			// �s�񏉊���
	D3DXMatrixPerspectiveFovLH(
		&m_Proj,							// �ˉe�}�g���b�N�X
		m_ViewAngle,						// ��p
		m_aspect,							// �A�X�y�N�g��
		m_Near,								// Near�v���[��
		m_Far);								// Far�v���[��

	// �r���[�g�����X�t�H�[��(���_���W�ϊ�)
	D3DXMatrixIdentity(&m_View);									// �s�񏉊���
	D3DXVECTOR3 vEye(m_position.x, m_position.y, m_position.z);		// �J�����ʒu

	if (m_updateType == enUpdateTypeTarget){
		m_direction = m_target - m_position;
		D3DXVec3Normalize(&m_direction,&m_direction);
		float t = fabsf(D3DXVec3Dot(&m_direction, &D3DXVECTOR3(0.0f, 1.0f, 0.0f)));
		if (fabsf((t - 1.0f)) < 0.00001f) {
			//���C�g�̕������ق�Y���ƕ��s�B
			m_up = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		}
		else {
			m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}
		D3DXMatrixLookAtLH(&m_View, &vEye, &m_target, &m_up);			// �r���[�}�g���b�N�X�ݒ�
	}
	else if (m_updateType == enUpdateTypeDirection){
		float t = fabsf(D3DXVec3Dot(&m_direction, &m_Axis));
		if (fabsf((t - 1.0f)) < 0.00001f) {
			//���C�g�̕������ق�Y���ƕ��s�B
			m_up = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		}
		else {
			m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}
		D3DXVECTOR3 target = vEye + m_direction;
		D3DXMatrixLookAtLH(&m_View, &vEye, &target, &m_up);
	}
	// �J�����̉�]�s��̎Z�o
	D3DXMatrixIdentity(&m_Rota);
	D3DXMatrixInverse(&m_Rota, nullptr, &m_View);
	m_Rota.m[3][0] = 0.0f;
	m_Rota.m[3][1] = 0.0f;
	m_Rota.m[3][2] = 0.0f;
	m_Rota.m[3][3] = 1.0f;

	D3DXMatrixIdentity(&m_RotaInv);
	D3DXMatrixInverse(&m_RotaInv, nullptr, &m_Rota);
}

void CCamera::SetCamera(LPD3DXEFFECT effect){
	effect->SetMatrix("Proj"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &m_Proj/*�ݒ肵�����s��ւ̃|�C���^*/);
	effect->SetMatrix("View"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &m_View/*�ݒ肵�����s��ւ̃|�C���^*/);
	effect->SetMatrix("g_CameraRotaInverse", &m_RotaInv);
}

void CCamera::SetFarNear(LPD3DXEFFECT effect){
	effect->SetVector("g_FarNear", reinterpret_cast<D3DXVECTOR4*>(&(D3DXVECTOR2(m_Far, m_Near))));
}