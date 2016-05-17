#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "ShadowRender.h"
#include "RenderContext.h"
#include "Enemy.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "EnemyManager.h"

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

	LockOnflag = false;

	// ライト関連の初期化
	count = 0;
	dir = D3DXVECTOR3(1, 1, 1);
	this->ConfigLight();

	m_IsIntersect.CollisitionInitialize(&m_transform.position,m_radius);
	C3DImage::SetImage();
	m_lockonEnemyIndex = 0;
}

void CPlayer::Update()
{
	this->UpdateLight();

	isTurn = false;


	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	float _X = 0.0f;
	if (LockOnflag){
		static float fHALF_PI = fPI / 2.0f;
		CEnemyManager* EnemyManager = (SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager")));
		CEnemy* Enemy = EnemyManager->GetEnemy(m_lockonEnemyIndex);
		D3DXVECTOR3 dist;
		dist = Enemy->GetPos() - m_transform.position;
		
		_X = fabsf(atan(dist.z / dist.x));
		if (dist.x >= 0.0f){
			if (dist.z >= 0.0f){
				_X = -fHALF_PI - _X;
			}
			else{
				_X = -fHALF_PI + _X;
			}
		}
		else if (dist.x < 0.0f){
			if (dist.z >= 0.0f){
				_X = fHALF_PI + _X;
			}
			else{
				_X = fHALF_PI - _X;
			}
		}
	}
	if (m_pInput->IsTriggerCancel() && LockOnflag == false)
	{
		LockOnflag = true;
		float Min;

		CEnemyManager* EnemyManager = (SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager")));
		CEnemy* Enemy;
		Min = 99999;	//番兵
		//敵20体分の距離の取得
		for (int K = 0; K < 20; K++)
		{
			Enemy = EnemyManager->GetEnemy(K);
			D3DXVECTOR3 dist;
			dist = Enemy->GetPos() - m_transform.position;
			float len = D3DXVec3Length(&dist);
			if (len < Min)
			{
				m_lockonEnemyIndex = K;
				Min = len;
			}
		}
	}
	if (m_pInput->IsTriggerDecsion() && LockOnflag == true)
	{
		LockOnflag = false;
	}

	if (m_pInput->IsTriggerSpace()){
		m_moveSpeed.y = MOVE_SPEED;
	}
	else if (m_pInput->IsPressUp()){
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
	if (m_pInput->IsPressShift() && m_pInput->IsPressRight()){
		m_transform.angle.y -= 0.1f;
	}
	else if (m_pInput->IsPressRight()){
		m_moveSpeed.x = MOVE_SPEED;
		isTurn = true;
		//右方向を向かせる。
		m_targetAngleY = D3DXToRadian(-90.0f);
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressLeft()){
		m_transform.angle.y += 0.1f;
	}
	else if (m_pInput->IsPressLeft()){
		m_moveSpeed.x = -MOVE_SPEED;
		isTurn = true;
		//左方向を向かせる
		m_targetAngleY = D3DXToRadian(90.0f);
	}
	if (LockOnflag){
		m_targetAngleY = _X;
	}

	//D3DXToRadianの値は各自で設定する。 例　正面D3DXToRadian(0.0f)
	//isTurnはUpdateの最初でfalseにして、回転させたい時にtrueにする。
	m_Turn.Update(isTurn, m_targetAngleY);

	//こいつを書かないと回転行列に乗算してくれない。
	m_currentAngleY = m_Turn.Getm_currentAngleY();

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