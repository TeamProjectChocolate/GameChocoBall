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

	g_currentAngleY = 0.0f;
	g_targetAngleY = 0.0f;
	g_turnSpeed = 0.0f;
	
	C3DImage::SetImage();

	m_IsIntersect.CollisitionInitialize(&m_transform.position,m_radius);
}

void CPlayer::Update()
{
	{
		isTurn = false;

		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

		const float MOVE_SPEED = 4.0f;

		if (m_pInput->IsTriggerCancel()){
			m_moveSpeed.y = 10.0f;
		}
		else if (m_pInput->IsPressUp()){
			m_moveSpeed.z = MOVE_SPEED;
			isTurn = true;
			//180�x��������B
			g_targetAngleY = D3DXToRadian(180.0f);
		}
		if (m_pInput->IsPressDown()){
			m_moveSpeed.z = -MOVE_SPEED;
			isTurn = true;
			//���ʂ���������B
			g_targetAngleY = D3DXToRadian(0.0f);
		}
		if (m_pInput->IsPressShift() && m_pInput->IsPressRight()){
			m_transform.angle.y -= 0.1f;
		}
		else if (m_pInput->IsPressRight()){
			m_moveSpeed.x = MOVE_SPEED;
			isTurn = true;
			//�E��������������B
			g_targetAngleY = D3DXToRadian(-90.0f);
		}
		if (m_pInput->IsPressShift() && m_pInput->IsPressLeft()){
			m_transform.angle.y += 0.1f;
		}
		else if (m_pInput->IsPressLeft()){
			m_moveSpeed.x = -MOVE_SPEED;
			isTurn = true;
			//����������������
			g_targetAngleY = D3DXToRadian(90.0f);
		}

		//��]����
		static const float fPI = 3.14159265358979323846f;
		if (isTurn) {
			float angleDiff = g_targetAngleY - g_currentAngleY;	//�ړI�p�x�܂łǂꂾ���񂹂������̂����v�Z����B
			float angleDiffAbs = fabsf(angleDiff);				//�񂷊p�x�̐�Βl���v�Z�B
			if (angleDiffAbs > 0.0001f) {						//�񂷊p�x�̑傫�������ɏ������ꍇ�͉񂳂Ȃ��B
				float turnDir = angleDiff / angleDiffAbs;		//��]������������v�Z����B
				if (angleDiffAbs > fPI) {						//��]������p�x��180�x���z���Ă��邩�𔻒肷��B
					//180�x���z�����]�̂��߉����B
					g_currentAngleY += 2.0f * fPI *  turnDir;	//���݂̊p�x��-90�x�Ȃ�270�x�A180�x�Ȃ�-180�x�ɂ���B
					turnDir *= -1.0f;							//�񂷕����𔽓]�B
				}
				g_turnSpeed = g_cTurnSpeed * turnDir;
			}
		}
		g_currentAngleY += g_turnSpeed;
		if (fabsf(g_targetAngleY - g_currentAngleY) < fabsf(g_turnSpeed) + 0.01f) {
			//�^�[���I���B
			g_turnSpeed = 0.0f;
			g_currentAngleY = g_targetAngleY;
		}

		m_IsIntersect.Intersect(&m_transform.position,&m_moveSpeed);//�v���C���[�̏����̍Ō�ɂȂ�ׂ�������

		SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), g_currentAngleY);//��]�s��

		C3DImage::Update();
		
		SINSTANCE(CShadowRender)->SetObjectPos(m_transform.position);
		SINSTANCE(CShadowRender)->SetShadowCameraPos(m_transform.position + D3DXVECTOR3(0.0f, 10.0f, 0.0f));
	}
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