#include "stdafx.h"
#include "Enemy.h"

CEnemy::~CEnemy(){ }

void CEnemy::Initialize()
{
	C3DImage::Initialize();
	m_transform.position = D3DXVECTOR3(0.0f, 0.0f, -2.0f);
	SetRotation(D3DXVECTOR3(0, 1, 0), 0.1f);
	//m_transform.angle = D3DXVECTOR3(0, 0, 0);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	m_radius = 0.1f;

	SetAlive(true);

	SetAlpha(1.0f);

	g_currentAngleY = 0.0f;
	g_targetAngleY = 0.0f;
	g_turnSpeed = 0.0f;

	

	C3DImage::SetImage();
	m_Rigidbody.Initialize(&m_transform.position, &m_transform.scale);
}

void CEnemy::Update()
{

	isTurn = false;

	//static const float fPI = 3.14159265358979323846f;
	//if (isTurn) {
	//	float angleDiff = g_targetAngleY - g_currentAngleY;	//�ړI�p�x�܂łǂꂾ���񂹂������̂����v�Z����B
	//	float angleDiffAbs = fabsf(angleDiff);				//�񂷊p�x�̐�Βl���v�Z�B
	//	if (angleDiffAbs > 0.0001f) {						//�񂷊p�x�̑傫�������ɏ������ꍇ�͉񂳂Ȃ��B
	//		float turnDir = angleDiff / angleDiffAbs;		//��]������������v�Z����B
	//		if (angleDiffAbs >  fPI) {						//��]������p�x��180�x���z���Ă��邩�𔻒肷��B
	//			//180�x���z�����]�̂��߉����B
	//			g_currentAngleY += 2.0f * fPI *  turnDir;	//���݂̊p�x��-90�x�Ȃ�270�x�A180�x�Ȃ�-180�x�ɂ���B
	//			turnDir *= -1.0f;							//�񂷕����𔽓]�B
	//		}
	//		g_turnSpeed = g_cTurnSpeed * turnDir;
	//	}
	//}
	//g_currentAngleY += g_turnSpeed;
	//if (fabsf(g_targetAngleY - g_currentAngleY) < fabsf(g_turnSpeed) + 0.01f) {
	//	//�^�[���I���B
	//	g_turnSpeed = 0.0f;
	//	g_currentAngleY = g_targetAngleY;
	//}

	//SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), g_currentAngleY);

	//m_IsIntersect.Intersect(&m_transform.position, &m_moveSpeed);//�v���C���[�̏����̍Ō�ɂȂ�ׂ�������

	m_Rigidbody.Update(&m_transform.position);
	C3DImage::Update();
}

void CEnemy::Draw(){
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

	m_Rigidbody.Draw();
	SetUpTechnique();
	C3DImage::Draw();
}

void CEnemy::OnDestroy()
{
	m_Rigidbody.OnDestroy();
}

void CEnemy::Build()
{
	m_Rigidbody.Build(m_transform.scale, m_transform.position);
}
