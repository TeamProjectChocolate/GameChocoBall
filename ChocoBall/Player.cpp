#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "ShadowRender.h"
#include "RenderContext.h"


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

	// ライト関連の初期化
	count = 0;
	dir = D3DXVECTOR3(1, 1, 1);
	this->ConfigLight();

	// これ以降は太郎作
	g_currentAngleY = 0.0f;
	g_targetAngleY = 0.0f;
	g_turnSpeed = 0.0f;
	
	C3DImage::SetImage();

	m_IsIntersect.CollisitionInitialize(&m_transform.position,m_radius);
}

void CPlayer::Update()
{
	this->UpdateLight();

	isTurn = false;

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	const float MOVE_SPEED = 8.0f;

	if (m_pInput->IsTriggerCancel()){
		m_moveSpeed.y = 5.0f;
	}
	else if (m_pInput->IsPressUp()){
		m_moveSpeed.z = MOVE_SPEED;
		isTurn = true;
		//180度向かせる。
		g_targetAngleY = D3DXToRadian(180.0f);
	}
	if (m_pInput->IsPressDown()){
		m_moveSpeed.z = -MOVE_SPEED;
		isTurn = true;
		//正面を向かせる。
		g_targetAngleY = D3DXToRadian(0.0f);
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressRight()){
		m_transform.angle.y -= 0.1f;
	}
	else if (m_pInput->IsPressRight()){
		m_moveSpeed.x = MOVE_SPEED;
		isTurn = true;
		//右方向を向かせる。
		g_targetAngleY = D3DXToRadian(-90.0f);
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressLeft()){
		m_transform.angle.y += 0.1f;
	}
	else if (m_pInput->IsPressLeft()){
		m_moveSpeed.x = -MOVE_SPEED;
		isTurn = true;
		//左方向を向かせる
		g_targetAngleY = D3DXToRadian(90.0f);
	}

	//回転処理
	//static const float fPI = 3.14159265358979323846f;
	if (isTurn) {
		float angleDiff = g_targetAngleY - g_currentAngleY;	//目的角度までどれだけ回せがいいのかを計算する。
		float angleDiffAbs = fabsf(angleDiff);				//回す角度の絶対値を計算。
		if (angleDiffAbs > 0.0001f) {						//回す角度の大きさが非常に小さい場合は回さない。
			float turnDir = angleDiff / angleDiffAbs;		//回転させる方向を計算する。
			if (angleDiffAbs > fPI) {						//回転させる角度が180度を越えているかを判定する。
				//180度を越える回転のため遠回り。
				g_currentAngleY += 2.0f * fPI *  turnDir;	//現在の角度を-90度なら270度、180度なら-180度にする。
				turnDir *= -1.0f;							//回す方向を反転。
			}
			g_turnSpeed = g_cTurnSpeed * turnDir;
		}
	}
	g_currentAngleY += g_turnSpeed;
	if (fabsf(g_targetAngleY - g_currentAngleY) < fabsf(g_turnSpeed) + 0.01f) {
		//ターン終わり。
		g_turnSpeed = 0.0f;
		g_currentAngleY = g_targetAngleY;
	}

	m_IsIntersect.Intersect(&m_transform.position, &m_moveSpeed);//プレイヤーの処理の最後になるべく書いて

	SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), g_currentAngleY);//回転行列

	C3DImage::Update();

	SINSTANCE(CShadowRender)->SetObjectPos(m_transform.position);
	SINSTANCE(CShadowRender)->SetShadowCameraPos(m_transform.position + D3DXVECTOR3(0.0f, 10.0f, 0.0f));
}

void CPlayer::Draw(){
	IMAGE3D* img = GetImage();
	LPD3DXMESH mesh = img->pModel->GetFrameRoot()->pMeshContainer->MeshData.pMesh;
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

void CPlayer::UpdateLight(){
	if (m_lightDir[0].x > 1.0f){
		dir.x *= -1;
	}
	else if (m_lightDir[0].x < -1.0f){
		dir.x *= -1;
	}
	m_lightDir[0].x += 0.1f * dir.x;

	if (m_lightDir[0].y > 1.0f){
		dir.y *= -1;
	}
	else if (m_lightDir[0].y < -1.0f){
		dir.y *= -1;
	}
	m_lightDir[0].y += 0.1f * dir.y;

	if (m_lightDir[0].z > 1.0f){
		dir.z *= -1;
	}
	else if (m_lightDir[0].z < -1.0f){
		dir.z *= -1;
	}
	m_lightDir[0].z += 0.1f * dir.z;
	count++;

	if (count % 60 == 0){
		D3DXVECTOR3 work = m_lightDir[0];
		m_lightDir[0] = m_lightDir[1];
		m_lightDir[1] = m_lightDir[2];
		m_lightDir[2] = m_lightDir[3];
		m_lightDir[3] = work;
		count = 0;
	}

	this->SetUpLight();
}

void CPlayer::ConfigLight(){
	// ディフューズライト(キャラライト)の向き設定(ライト1～4)
	m_lightDir[0] = D3DXVECTOR3(0.707f, 0.707f, 0.0f);
	m_lightDir[1] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_lightDir[2] = D3DXVECTOR3(1.0f, -1.0f, 0.5f);
	m_lightDir[3] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	// ディフューズライト(キャラライト)の色設定(ライト1～4)
	m_lightColor[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_lightColor[1] = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	m_lightColor[2] = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_lightColor[3] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	// アンビエントライト(環境光)の強さ設定
	D3DXVECTOR4 ambientLight;
	ambientLight = D3DXVECTOR4(0.2f, 0.0f, 0.0f, 100.0f);

	// ライトの設定を反映
	ReflectionLight(ambientLight);
}

void CPlayer::ReflectionLight(D3DXVECTOR4 ambient){
	this->SetUpLight();
	m_light.SetAmbientLight(ambient);
}

void CPlayer::SetUpLight(){
	for (short num = 0; num < NUM_DIFFUSE_LIGHT; num++){
		D3DXVECTOR4 dir;
		dir.x = m_lightDir[num].x;
		dir.y = m_lightDir[num].y;
		dir.z = m_lightDir[num].z;
		dir.w = 1.0f;
		m_light.SetDiffuseLightDirection(num, dir);
		m_light.SetDiffuseLightColor(num, m_lightColor[num]);
	}
	SINSTANCE(CRenderContext)->SetCurrentLight(&m_light);
}