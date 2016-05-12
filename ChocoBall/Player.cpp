#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "ShadowRender.h"


CPlayer::~CPlayer(){ }


void CPlayer::Initialize()
{
	C3DImage::Initialize();
	m_pInput = SINSTANCE(CInputManager)->GetInput();
	m_transform.position = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	SetRotation(D3DXVECTOR3(0, 1, 0), 0.1f);
	m_transform.scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	m_radius = 1.0f;

	SetAlive(true);

	SetAlpha(1.0f);
	
	m_Turn.Initialize();
	m_IsIntersect.CollisitionInitialize(&m_transform.position,m_radius);
	C3DImage::SetImage();
}

void CPlayer::Update()
{
	isTurn = false;

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	if (m_pInput->IsTriggerCancel()){
		m_moveSpeed.y = 5.0f;
	}
	else if (m_pInput->IsPressUp()){
		m_moveSpeed.z = MOVE_SPEED;
		isTurn = true;
		//180�x��������B
		m_targetAngleY = D3DXToRadian(180.0f);
	}
	if (m_pInput->IsPressDown()){
		m_moveSpeed.z = -MOVE_SPEED;
		isTurn = true;
		//���ʂ���������B
		m_targetAngleY = D3DXToRadian(0.0f);
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressRight()){
		m_transform.angle.y -= 0.1f;
	}
	else if (m_pInput->IsPressRight()){
		m_moveSpeed.x = MOVE_SPEED;
		isTurn = true;
		//�E��������������B
		m_targetAngleY = D3DXToRadian(-90.0f);
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressLeft()){
		m_transform.angle.y += 0.1f;
	}
	else if (m_pInput->IsPressLeft()){
		m_moveSpeed.x = -MOVE_SPEED;
		isTurn = true;
		//����������������
		m_targetAngleY = D3DXToRadian(90.0f);
	}

	//D3DXToRadian�̒l�͊e���Őݒ肷��B ��@����D3DXToRadian(0.0f)
	//isTurn�͊eUpdate�̍ŏ���false�ɂ��āA��]������������true�ɂ���B
	m_Turn.Update(isTurn,m_targetAngleY);

	//�����������Ȃ��Ɖ�]�s��ɏ�Z���Ă���Ȃ��B
	m_currentAngleY = m_Turn.Getm_currentAngleY();

	//�v���C���[�̏����̍Ō�ɂȂ�ׂ�������
	m_IsIntersect.Intersect(&m_transform.position, &m_moveSpeed);	

	//��]�s��
	SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f),m_currentAngleY);

	C3DImage::Update();

	SINSTANCE(CShadowRender)->SetObjectPos(m_transform.position);
	SINSTANCE(CShadowRender)->SetShadowCameraPos(m_transform.position + D3DXVECTOR3(0.0f, 10.0f, 0.0f));

}

void CPlayer::Draw(){
	IMAGE3D* img = GetImage();
	LPD3DXMESH mesh = img->pMesh;
	LPDIRECT3DVERTEXBUFFER9 pVB;
	mesh->GetVertexBuffer(&pVB);
	int numVertex = mesh->GetNumVertices();
	D3DVERTEXBUFFER_DESC desc;
	pVB->GetDesc(&desc);
	int stride = desc.Size / numVertex;
	char* pData;
	pVB->Lock(0, 0, (void**)&pData, D3DLOCK_DISCARD);
	float YMax, YMin;
	YMax = -FLT_MAX;
	YMin = FLT_MAX;
	for (int i = 0; i < numVertex; i++){
		float* pos = (float*)pData;
		YMax = max(YMax, pos[1]);
		YMin = min(YMin, pos[1]);
		pData += stride;
	}
	float size = YMax + fabsf(YMin);
	float center = (YMax + YMin)*0.5f;
	pVB->Unlock();

	SetUpTechnique();
	C3DImage::Draw();
}