#include "stdafx.h"
#include "Camera.h"
#include "GraphicsDevice.h"
#include "Effect.h"

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
	D3DXVECTOR3 vLookAt(m_target.x, m_target.y, m_target.z);		// �����ʒu�@�J��������
	D3DXVECTOR3 vUpVec(m_up.x, m_up.y, m_up.z);						// ������@�J�����X��
	D3DXMatrixLookAtLH(&m_View, &vEye, &vLookAt, &vUpVec);			// �r���[�}�g���b�N�X�ݒ�
}

void CCamera::SetCamera(LPD3DXEFFECT effect){
	// ���C�g�ݒ�(���F�A���ʔ���)
	D3DXVECTOR3 vDirec(0, -1, -1);		// ���C�g����
	D3DLIGHT9 light;					// ���C�g�\����
	ZeroMemory(&light, sizeof(D3DLIGHT9));		// ������
	light.Type = D3DLIGHT_DIRECTIONAL;		// ���s����
	// �g�U��
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	// ���ʌ�
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;

	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vDirec);		// ���C�g�����̐ݒ�
	(*graphicsDevice()).SetLight(0, &light);			// ���C�g�ݒ�
	(*graphicsDevice()).LightEnable(0, TRUE);		// ���C�g���Ă�
	// Z�o�b�t�@�[�A���C�g�̐ݒ�
	(*graphicsDevice()).SetRenderState(D3DRS_LIGHTING, TRUE);	// ���C�g��L��
	(*graphicsDevice()).SetRenderState(D3DRS_AMBIENT, 0x00aaaaaa);	// ������ݒ�
	(*graphicsDevice()).SetRenderState(D3DRS_SPECULARENABLE, TRUE);	// ���ʔ��˗L��
	(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, TRUE);			// Z�o�b�t�@�[��L��

	effect->SetMatrix("Proj"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &m_Proj/*�ݒ肵�����s��ւ̃|�C���^*/);
	effect->SetMatrix("View"/*�G�t�F�N�g�t�@�C�����̕ϐ���*/, &m_View/*�ݒ肵�����s��ւ̃|�C���^*/);
}