#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "ShadowRender.h"
#include "RenderContext.h"
#include "Enemy.h"
#include "GameObject.h"
#include "ObjectManager.h"
//#include "EnemyManager.h"
#include "LockOn.h"

CPlayer::~CPlayer(){ }

void CPlayer::Initialize()
{

	C3DImage::Initialize();
	m_pInput = SINSTANCE(CInputManager)->GetCurrentInput();
	m_transform.position = D3DXVECTOR3(0.00f, 0.0f, -49.42f);
	SetRotation(D3DXVECTOR3(0, 1, 0), 0.1f);
	m_transform.scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_Up.x = 0.0f;
	m_Up.y = 1.0f;
	m_Up.z = 0.0f;
	
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	m_radius = 1.0f;

	SetAlive(true);
	SetAlpha(1.0f);

	LockOnflag = false;
	Shotflag = false;

	m_Courcedef.Initialize();

	// ライト関連の初期化
	this->ConfigLight();

	m_IsIntersect.CollisitionInitialize(&m_transform.position,m_radius);

	C3DImage::SetImage();

	m_lockonEnemyIndex = 0;
}

void CPlayer::Update()
{
	SINSTANCE(CInputManager)->IsInputChanged(&m_pInput);

	this->UpdateLight();

	isTurn = false;

	//if (m_pInput->IsTriggerShift())
	//{
	//	Shotflag = true;
	//}
	if (m_pInput->IsTriggerSpace())
	{
		m_moveSpeed.y = 8.0f;
	}
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//直行するベクトルを求める。
	COURCE_BLOCK Cource = m_Courcedef.FindCource(m_transform.position);
	m_V1 = Cource.endPosition - Cource.startPosition;
	D3DXVec3Normalize(&V1, &m_V1);//3D ベクトルを正規化したベクトルを返す。
	D3DXVec3Cross(&m_V2, &V1, &m_Up);//2つの3Dベクトルの上方向の外積を求める→直行するV2が見つかる。
	D3DXVec3Normalize(&V2, &m_V2);

	//m_V3 = V1 + V2;
	//V3 = D3DXVec3Length(&m_V3);

	float _X = 0.0f;


	if (m_pInput->IsPressUp()){
		m_moveSpeed.z = MOVE_SPEED;
		isTurn = true;
		//180度向かせる。
		m_targetAngleY = D3DXToRadian(180.0f);
	}
	else if (m_pInput->IsPressDown()){
		m_moveSpeed.z = -MOVE_SPEED;
		isTurn = true;
		//正面を向かせる。
		m_targetAngleY = D3DXToRadian(0.0f);
	}

	if (m_pInput->IsPressRight()){
		m_moveSpeed.x = MOVE_SPEED;
		isTurn = true;
		//右方向を向かせる。
		m_targetAngleY = D3DXToRadian(-90.0f);
	}
	if (m_pInput->IsPressLeft()){
		m_moveSpeed.x = -MOVE_SPEED;
		isTurn = true;
		//左方向を向かせる
		m_targetAngleY = D3DXToRadian(90.0f);
	}

	//コース定義にしたがってプレイヤーの進行方向と曲がり方を指定
	D3DXVECTOR3 t0, t1;
	t0 = V1 * m_moveSpeed.z;
	t1 = V2 * -m_moveSpeed.x;
	t0 += t1;
	m_moveSpeed.x = t0.x;
	m_moveSpeed.z = t0.z;
	//m_moveSpeed.x = m_moveSpeed.x * -m_V3.x;
	//m_moveSpeed.z = m_moveSpeed.z * m_V3.z;

	float L;
	D3DXVECTOR3		NV2;
	float			cos;
	D3DXVECTOR3		Back;
	D3DXVECTOR3     NV3;
	Back.x = 0.0f;
	Back.y = 0.0f;
	Back.z = -1.0f;

	D3DXVECTOR3 moveXZ = m_moveSpeed;
	moveXZ.y = 0.0f;
	L = D3DXVec3Length(&moveXZ);//m_moveSpeedのベクトルの大きさを返す、√の計算もしてくれる。
	if (L > 0)
	{
		D3DXVec3Normalize(&NV2, &moveXZ);
		D3DXVec3Cross(&NV3, &NV2, &Back);
		cos = D3DXVec3Dot(&NV2, &Back);///2つの3Dベクトルの上方向の内積を求める→V1とV2のなす角のcosθが見つかる。
		m_targetAngleY = acos(cos);
		if (NV3.y > 0)
		{
			m_targetAngleY = m_targetAngleY*-1;
		}
	}

	//ロックオン状態にする。
	if (m_pInput->IsTriggerCancel() && LockOnflag == false)
	{
		LockOnflag = true;
		m_lockonEnemyIndex = m_LockOn.FindNearEnemy(m_transform.position);
	}
	//ロックオン状態中の回転の計算
	if (LockOnflag)
	{
		_X = m_LockOn.LockOnRotation(_X, m_transform.position, m_lockonEnemyIndex);
	}

	//ロックオン状態の解除
	if (m_pInput->IsTriggerDecsion() && LockOnflag == true)
	{
		LockOnflag = false;
	}

	//ロックオン状態の時に常にプレイヤーを敵に向かせる
	if (LockOnflag){
		m_targetAngleY = _X;
	}

	//D3DXToRadianの値は各自で設定する。 例　正面D3DXToRadian(0.0f)
	//isTurnはUpdateの最初でfalseにして、回転させたい時にtrueにする。
	m_currentAngleY = m_Turn.Update(isTurn, m_targetAngleY);

	//プレイヤーの処理の最後になるべく書いて
	m_IsIntersect.Intersect(&m_transform.position, &m_moveSpeed);

	//回転行列
	SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_currentAngleY);

	C3DImage::Update();

	SINSTANCE(CShadowRender)->SetObjectPos(m_transform.position);
	SINSTANCE(CShadowRender)->SetShadowCameraPos(m_transform.position + D3DXVECTOR3(0.0f, 10.0f, 0.0f));
}

void CPlayer::Draw(){
	/*IMAGE3D* img = GetImage();
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
		YMin = Minx(YMin, pos[1]);
		pData += stride;
	}
	float size = YMax + fabsf(YMin);
	float center = (YMax + YMin)*0.5f;
	pVB->Unlock();*/

	SetUpTechnique();
	C3DImage::Draw();
}

void CPlayer::UpdateLight(){
	this->SetUpLight();
}

void CPlayer::ConfigLight(){
	// ディフューズライト(キャラライト)の向き設定(ライト1～4)
	m_lightDir[0] = D3DXVECTOR3(0.707f, 0.707f, 0.0f);
	m_lightDir[1] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_lightDir[2] = D3DXVECTOR3(1.0f, -1.0f, 0.5f);
	m_lightDir[3] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	// ディフューズライト(キャラライト)の色設定(ライト1～4)
	m_lightColor[0] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_lightColor[1] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_lightColor[2] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
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