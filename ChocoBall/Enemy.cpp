#include "stdafx.h"
#include "Enemy.h"

CEnemy::~CEnemy(){ }

void CEnemy::Initialize()
{
	C3DImage::Initialize();
	//m_transform.position = D3DXVECTOR3(-2.5f, 0.0f, -5.0f);
	m_transform.position = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	SetRotation(D3DXVECTOR3(0, 1, 0), 0.1f);
	//m_transform.angle = D3DXVECTOR3(0, 0, 0);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_moveSpeed.x = 0.05f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	m_radius = 0.1f;

	SetAlive(true);

	SetAlpha(1.0f);

	g_currentAngleY = 0.0f;
	g_targetAngleY = 0.0f;
	g_turnSpeed = 0.0f;

	flg = true;

	C3DImage::SetImage();
	m_Rigidbody.Initialize(&m_transform.position, &m_transform.scale);
}

void CEnemy::Update()
{

	
	m_transform.position.x += m_moveSpeed.x;
	if (flg == true){
		if (m_transform.position.x > 2.5)
		{
			m_moveSpeed.x *= -1;
			flg = false;
		}
	}
	else{
		if (m_transform.position.x < -2.5)
		{
			m_moveSpeed.x *= -1;
			flg = true;
		}
	}

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
