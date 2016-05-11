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
	//	float angleDiff = g_targetAngleY - g_currentAngleY;	//目的角度までどれだけ回せがいいのかを計算する。
	//	float angleDiffAbs = fabsf(angleDiff);				//回す角度の絶対値を計算。
	//	if (angleDiffAbs > 0.0001f) {						//回す角度の大きさが非常に小さい場合は回さない。
	//		float turnDir = angleDiff / angleDiffAbs;		//回転させる方向を計算する。
	//		if (angleDiffAbs >  fPI) {						//回転させる角度が180度を越えているかを判定する。
	//			//180度を越える回転のため遠回り。
	//			g_currentAngleY += 2.0f * fPI *  turnDir;	//現在の角度を-90度なら270度、180度なら-180度にする。
	//			turnDir *= -1.0f;							//回す方向を反転。
	//		}
	//		g_turnSpeed = g_cTurnSpeed * turnDir;
	//	}
	//}
	//g_currentAngleY += g_turnSpeed;
	//if (fabsf(g_targetAngleY - g_currentAngleY) < fabsf(g_turnSpeed) + 0.01f) {
	//	//ターン終わり。
	//	g_turnSpeed = 0.0f;
	//	g_currentAngleY = g_targetAngleY;
	//}

	//SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), g_currentAngleY);

	//m_IsIntersect.Intersect(&m_transform.position, &m_moveSpeed);//プレイヤーの処理の最後になるべく書いて

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
