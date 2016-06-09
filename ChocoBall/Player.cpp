#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "ShadowRender.h"
#include "RenderContext.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "PlayerParam.h"
#include "ParticleEmitter.h"
#include "MoveFloor.h"
#include "StageTable.h"

CPlayer* g_player = NULL;
CPlayer::~CPlayer(){  }

void CPlayer::Initialize()

{
	parent = NULL;
	g_player = this;
	C3DImage::Initialize();
	m_pInput = SINSTANCE(CInputManager)->GetCurrentInput();
	m_transform.position = PlayerTransformArray[m_StageID].pos;
	m_transform.angle = PlayerTransformArray[m_StageID].rotation;
	m_transform.scale = PlayerTransformArray[m_StageID].scale;

	// Unityから出力したポジション情報を最適化
	m_transform.position.x *= -1.0f;
	m_transform.position.z *= -1.0f;

	RV0 = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	localPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	m_radius = 1.0f;

	deadTimer = 0.0f;

	SetAlive(true);
	SetAlpha(1.0f);
	
	LockOnflag = false;
	Shotflag = false;
	Jumpflag = false;
	ChocoBall = false;
	
	GamaOverFlag = false;
	BusterEnemyNum = 0;
	m_size.x = 1.0f;
	m_size.y = 2.0f;
	m_size.z = 1.0f;

	m_GameState = GAMEEND_ID::CONTINUE;

	m_Courcedef.SetStageID(m_StageID);
	m_Courcedef.Initialize();

	// ライト関連の初期化
	this->ConfigLight();
	
	m_IsIntersect.CollisitionInitialize(&m_transform.position, m_radius);
	
	m_CBManager =NULL;

	C3DImage::SetImage();

	deadTimer = 0.0f;
	m_lockonEnemyIndex = 0;	
	m_pEmitter = CParticleEmitter::EmitterCreate(
		_T("ParticleEmitterTEST"),
		PARTICLE_TYPE::FIRE,
		m_transform.position,
		SINSTANCE(CObjectManager)->FindGameObject<CCourceCamera>(_T("Camera"))->GetCamera()
	);
	CParticleEmitter::EmitterCreate(
		_T("ParticleEmitterPORIGON"),
		PARTICLE_TYPE::PORIGON,
		m_transform.position,
		SINSTANCE(CObjectManager)->FindGameObject<CCourceCamera>(_T("Camera"))->GetCamera()
		);

}

void CPlayer::SetParent(MoveFloor* parent)
{
	//親が設定されたので、ワールド座標を求めるために。一旦Updateを呼び出す。
	
	if (parent != NULL){
		//親が設定されたので、ローカル座標を親のローカル座標に変換する。
		D3DXMATRIX mParentWorldInv = parent->GetWorldMatrix();
		D3DXMatrixInverse(&mParentWorldInv, NULL, &mParentWorldInv);
		D3DXVECTOR4 pos;
		D3DXVec3Transform(&pos, &m_transform.position, &mParentWorldInv);
		localPosition.x = pos.x;
		localPosition.y = pos.y;
		localPosition.z = pos.z;
		this->parent = parent;
	}
	else if (this->parent != NULL){
		
		D3DXMATRIX mParentWorld = this->parent->GetWorldMatrix();
		D3DXVECTOR4 pos;
		D3DXVec3Transform(&pos, &localPosition, &mParentWorld);
		localPosition.x = pos.x;
		localPosition.y = pos.y;
		localPosition.z = pos.z;

		m_transform.position.x = pos.x;
		m_transform.position.y = pos.y;
		m_transform.position.z = pos.z;
		this->parent = parent;
	}
}

void CPlayer::Update()
{
	if (m_GameState == GAMEEND_ID::CONTINUE)
	{
		//親がいるときの処理
		if (parent)
		{
			D3DXMATRIX mParentWorld = parent->GetWorldMatrix();
			//親のワールド行列を乗算して、ローカル座標をワールド座標に変換する

			D3DXVECTOR4 pos;
			D3DXVec3Transform(&pos, &localPosition, &mParentWorld);
			m_transform.position.x = pos.x + parent->GetMoveSpeed().x;
			m_transform.position.y = pos.y + parent->GetMoveSpeed().y;
			m_transform.position.z = pos.z + parent->GetMoveSpeed().z;
		}
		
		// デバイスが切り替わった場合は自動で切り替える
		SINSTANCE(CInputManager)->IsInputChanged(&m_pInput);

		m_currentAnimNo = 0;		

		// ライトの更新
		this->UpdateLight();

		// メインシーンの状態を管理する処理
		StateManaged();

		//ゲームパッドでのプレイヤーの移動。
		Move();

		// アニメーション再生関数を呼び出す
		m_animation.PlayAnimation(m_currentAnimNo, 0.1f);

		//プレイヤーの挙動をコース定義に沿ったものに補正する処理
		BehaviorCorrection();

		//ロックオン処理
		LockOn();

		if (m_CBManager != NULL)
		{
			//チョコボールに当たっているかの処理
			if (m_HitFlag = m_CBManager->IsHit(m_transform.position, m_size))
			{
				//チョコボールに当たったらの処理
				ChocoHit();
			}
		}

		if (GamaOverFlag==false)//ゲームオーバーになっていない時の処理
		{
			
			//プレイヤーの処理の最後になるべく書いて
			m_IsIntersect.Intersect(&m_transform.position, &m_moveSpeed);

			//着地しているのでフラグはfalse
			if (m_IsIntersect.IsHitGround())
			{
				Jumpflag = false;
			}

			// 弾発射処理
			BulletShot();

			//回転行列
			SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_currentAngleY);
		}
		else if (GamaOverFlag == true)
		{
			//ゲームオーバー状態でのチョコボールに流される処理
			RollingPlayer();

		}
		C3DImage::Update();

		// 自分の周囲にパーティクル発生
		m_pEmitter->SetEmitPos(m_transform.position);
	}

	SINSTANCE(CShadowRender)->SetObjectPos(m_transform.position);
	SINSTANCE(CShadowRender)->SetShadowCameraPos(m_transform.position + D3DXVECTOR3(0.0f, 10.0f, 0.0f));

	int size = m_bullets.size();
	for (int idx = 0; idx < size; idx++){
		m_bullets[idx]->Update();
	}
}

void CPlayer::Draw(){
	
	SetUpTechnique();
	C3DImage::Draw();

	int size = m_bullets.size();
	for (int idx = 0; idx < size; idx++){
		m_bullets[idx]->Draw();
	}

	// 絶対にここで呼べよ！　絶対だぞっ！？
	ExcuteDeleteBullets();
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

void CPlayer::Move()
{
	isTurn = false;


	if (m_pInput->IsTriggerSpace() && Jumpflag == false)
	{
		m_moveSpeed.y = PLAYER_JUMP_POWER;
		Jumpflag = true;
	}

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	float X = m_pInput->GetStickL_XFloat();
	float Y = m_pInput->GetStickL_YFloat();

	//前後の動き
	if (fabs(Y) > 0.0f)
	{

		m_moveSpeed.z = Y * MOVE_SPEED;
		isTurn = true;
		m_currentAnimNo = 1;
	}

	//左右の動き
	if (fabsf(X) > 0.0f)
	{
		m_moveSpeed.x = X * MOVE_SPEED;
		isTurn = true;
		m_currentAnimNo = 1;
	}
	//D3DXToRadianの値は各自で設定する。 例　正面D3DXToRadian(0.0f)
	//isTurnはUpdateの最初でfalseにして、回転させたい時にtrueにする。
	m_currentAngleY = m_Turn.Update(isTurn, m_targetAngleY);
}

void CPlayer::LockOn()
{
	float _X = 0.0f;

	//ロックオン状態にする。
	if (m_pInput->IsTriggerLeftShift() && LockOnflag == false)
	{
		m_lockonEnemyIndex = m_LockOn.FindNearEnemy(m_transform.position);
		if (m_lockonEnemyIndex != -1){
			LockOnflag = true;
		}
		
	}
	//ロックオン状態の解除
	else if (m_pInput->IsTriggerLeftShift() && LockOnflag == true)
	{
		LockOnflag = false;
	}
	//ロックオン状態中の回転の計算
	if (LockOnflag)
	{
		if (m_lockonEnemyIndex == -1){
			LockOnflag = false;
		}
		else{
			_X = m_LockOn.LockOnRotation(_X, m_transform.position, m_lockonEnemyIndex);
		}
	}
	//ロックオン状態の時に常にプレイヤーを敵に向かせる
	if (LockOnflag){
		m_targetAngleY = _X;
	}

}

void CPlayer::BehaviorCorrection()
{
	D3DXVECTOR3		V1;
	D3DXVECTOR3		V2;
	D3DXVECTOR3		Up;

	Up.x = 0.0f;
	Up.y = 1.0f;
	Up.z = 0.0f;

	//直行するベクトルを求める。
	COURCE_BLOCK Cource = m_Courcedef.FindCource(m_transform.position);
	V1 = Cource.endPosition - Cource.startPosition;
	D3DXVec3Normalize(&V1, &V1);//3D ベクトルを正規化したベクトルを返す。
	D3DXVec3Cross(&V2, &V1,&Up);//2つの3Dベクトルの上方向の外積を求める→直行するV2が見つかる。
	D3DXVec3Normalize(&V2, &V2);

	//コース定義にしたがってプレイヤーの進行方向と曲がり方を指定
	D3DXVECTOR3 t0, t1;
	t0 = V1 * m_moveSpeed.z;
	t1 = V2 * -m_moveSpeed.x;
	t0 += t1;
	m_moveSpeed.x = t0.x;
	m_moveSpeed.z = t0.z;

	//コース定義に従ったプレイヤーの回転の処理
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

}

void CPlayer::StateManaged()
{
	CEnemyManager* EnemyManager = (SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager")));
	m_lockonEnemyIndex = m_LockOn.FindNearEnemy(m_transform.position);
	if (m_lockonEnemyIndex != -1){
		EnemyBase* Enemy = EnemyManager->GetEnemy(m_lockonEnemyIndex);
		D3DXVECTOR3 dist;
		dist = Enemy->GetPos() - m_transform.position;
		float R;
		R = D3DXVec3Length(&dist);//ベクトルの長さを計算

		if (R <= 1)
		{
			m_GameState = GAMEEND_ID::OVER;
			return;
		}
	}
	//ゲームオーバー処理
	if (m_transform.position.y <= -10.0f)
	{
		m_GameState = GAMEEND_ID::OVER;
		return;
	}

	//ゲームクリア
	D3DXVECTOR3 Endposition;
	Endposition = m_Courcedef.EndCource();
	D3DXVECTOR3 StageEndPosition;
	StageEndPosition = Endposition - m_transform.position;
	float Kyori = D3DXVec3Length(&StageEndPosition);
	if (Kyori < 2)
	{
		m_GameState = GAMEEND_ID::CLEAR;
		return;
	}
}

void CPlayer::BulletShot()
{
	if (m_pInput->IsTriggerRightShift())
	{

		//プレイヤーの向いているベクトルを計算
		D3DXVec3Normalize(&RV0, &RV0);
		D3DXMatrixRotationY(&Rot, m_currentAngleY);
		D3DXVec3Transform(&RV1, &RV0, &Rot);


		Bullet* bullet = new Bullet;
		bullet->Initialize();
		bullet->SetPos(m_transform.position);
		bullet->SetDir(RV1);
		bullet->SetBulletSpeed(3.0f);
		m_bullets.push_back(bullet);
	}

	//プレイヤーと弾の距離が20mになると弾が自動でDeleteする。
	int size = m_bullets.size();
	for (int idx = 0; idx < size; idx++){
		D3DXVECTOR3 V5;
		V5 = m_bullets[idx]->GetPos() - m_transform.position;
		float length = D3DXVec3Length(&V5);
		length = fabs(length);
		if (length > BULLET_LENG)
		{
			DeleteBullet(m_bullets[idx]);
		}
	}
}

void CPlayer::DeleteBullet(Bullet* bullet){
	m_Deletebullets.push_back(bullet);
}

void CPlayer::ExcuteDeleteBullets(){
	vector<Bullet*>::iterator itr;
	int size = m_Deletebullets.size();
	for (int idx = 0; idx < size; idx++){
		for (itr = m_bullets.begin(); itr != m_bullets.end();){
			if (m_Deletebullets[idx] == *itr){
				SAFE_DELETE(*itr);
				itr = m_bullets.erase(itr);
				break;
			}
			else{
				itr++;
			}
		}
	}
	m_Deletebullets.clear();
}

void CPlayer::ChocoHit()
{
	GamaOverFlag = true;
	btRigidBody* rb = m_IsIntersect.GetRigidBody();//プレイヤーの剛体を取得
	m_IsIntersect.GetSphereShape()->setLocalScaling(btVector3(0.3f, 0.3f, 0.3f));//プレイヤーの球を小さく設定し、チョコボールに埋もれるようにしている。
	rb->setMassProps(1.0f, btVector3(0.1f, 0.1f, 0.1f));//第一引数は質量、第二引数は回転のしやすさ
	//rb->applyForce(btVector3(0.0f, 100.0f, 0.0f), btVector3(1.0f, 1.0f, 1.0f));//チョコボールに当たって吹っ飛ぶ力を設定
	m_animation.SetAnimSpeed(2.0f);//アニメーション再生速度を設定
}

void CPlayer::RollingPlayer()
{
	btRigidBody* rb = m_IsIntersect.GetRigidBody();//プレイヤーの剛体を取得

	//物理エンジンで計算した移動をプレイヤーに反映
	btVector3 pos = rb->getWorldTransform().getOrigin();
	m_transform.position.x = pos.x();
	m_transform.position.y = pos.y();
	m_transform.position.z = pos.z();

	//物理エンジンで計算した回転をプレイヤーに反映
	btQuaternion rot = rb->getWorldTransform().getRotation();
	m_transform.angle.x = rot.x();
	m_transform.angle.y = rot.y();
	m_transform.angle.z = rot.z();
	m_transform.angle.w = rot.w();

	//ゲームオーバーになるまでの待機時間の設定
	deadTimer += 1.0 / 60.0f;
	if (deadTimer >= 2.0f){
		m_GameState = GAMEEND_ID::OVER;
	}
}

