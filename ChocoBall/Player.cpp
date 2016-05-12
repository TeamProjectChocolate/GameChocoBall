#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "ShadowRender.h"
#include "RenderContext.h"


CPlayer::~CPlayer(){ }

struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	D3DXVECTOR3 hitPos;

	SweepResultGround()
	{
		isHit = false;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//無視。
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;
		 convexResult.m_hitNormalLocal.x();
		hitPointNormal.y = convexResult.m_hitNormalLocal.y();
		hitPointNormal.z = convexResult.m_hitNormalLocal.z();
		float d = D3DXVec3Dot(&hitPointNormal,&CVec3Up);
		if (d < 0.0f) {
			//当たってない。
			return 0.0f;
		}
		if (acosf(d) > PI * 0.2) {
			//ホントは地面かどうかとかの属性を見るのがベストなんだけど、今回は角度で。
			return 0.0f;
		}
		isHit = true;
	
		hitPos.x = convexResult.m_hitPointLocal.x();
		hitPos.y = convexResult.m_hitPointLocal.y();
		hitPos.z = convexResult.m_hitPointLocal.z();
		return 0.0f;
	}
};
struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	D3DXVECTOR3 hitNormalXZ;
	bool isHit;
	D3DXVECTOR3 hitPos;
	SweepResultWall()
	{
		isHit = false;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//無視。
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;
		hitPointNormal.x = convexResult.m_hitNormalLocal.x();
		hitPointNormal.y = convexResult.m_hitNormalLocal.y();
		hitPointNormal.z = convexResult.m_hitNormalLocal.z();
		float d = D3DXVec3Dot(&hitPointNormal, &CVec3Up);
		if (acosf(d) < PI * 0.2) {
			//ホントは地面かどうかとかの属性を見るのがベストなんだけど、今回は角度で。
			return 0.0f;
		}
		isHit = true;
		//XZ平面での法線。
		hitNormalXZ.x = hitPointNormal.x;
		hitNormalXZ.y = 0.0f;
		hitNormalXZ.z = hitPointNormal.z;
		D3DXVec3Normalize(&hitNormalXZ,&hitPointNormal);

		btTransform transform = convexResult.m_hitCollisionObject->getWorldTransform();

		
		hitPos.x = convexResult.m_hitPointLocal.x();
		hitPos.x = convexResult.m_hitPointLocal.y();
		hitPos.x = convexResult.m_hitPointLocal.z();
		return 0.0f;
	}
};

void CPlayer::Initialize()
{
	C3DImage::Initialize();
	m_pInput = SINSTANCE(CInputManager)->GetInput();
	m_transform.position = D3DXVECTOR3(0, 2.0f, 0.0f);
	SetRotation(D3DXVECTOR3(0, 1, 0), 0.1f);
	//m_transform.angle = D3DXVECTOR3(0, 0, 0);
	m_transform.scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	m_radius = 1.0f;

	SetAlive(true);

	count = 0;
	dir = D3DXVECTOR3(1, 1, 1);
	ConfigLight();

	SetAlpha(0.5f);

	g_currentAngleY = 0.0f;
	g_targetAngleY = 0.0f;
	g_turnSpeed = 0.0f;
	
	//コリジョン初期化。
	m_collisionShape = new btSphereShape(m_radius);
	float mass = 1000.0f;
	btTransform rbTransform;
	rbTransform.setIdentity();
	rbTransform.setOrigin(btVector3(m_transform.position.x, m_transform.position.y, m_transform.position.z));
	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(rbTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserIndex(0);
	//ワールドに追加。
	g_bulletPhysics.AddRigidBody(m_rigidBody);

	C3DImage::SetImage();
}

void CPlayer::Update()
{

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

	SetUpLight();

	{
		static float deltaTime = (1.0f / 60.0f);
		static D3DXVECTOR3 gravity(0.0f, -9.8f, 0.0f);
		D3DXVECTOR3 addGravity = gravity;
		addGravity *= deltaTime;
		m_moveSpeed += (addGravity);
		D3DXVECTOR3 addPos;
		addPos = m_moveSpeed;
		addPos *= deltaTime;
		//XZ平面を調べる。
		{
			int loopCount = 0;
			while (true) {
				btTransform start, end;
				start.setIdentity();
				end.setIdentity();
				start.setOrigin(btVector3(m_transform.position.x, m_transform.position.y, m_transform.position.z));
				D3DXVECTOR3 newPos;
				SweepResultWall callback;
				D3DXVECTOR3 addPosXZ = addPos;
				addPosXZ.y = 0.0f;
				if (D3DXVec3Length(&addPosXZ) > 0.0001f) {
					newPos += (m_transform.position, addPosXZ);
					end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

					g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
				}
				if (callback.isHit) {
					//当たった。
					//壁。
					addPos.x = callback.hitPos.x - m_transform.position.x;
					addPos.z = callback.hitPos.z - m_transform.position.z;

					D3DXVECTOR3 t;
					t.x = -addPos.x;
					t.y = 0.0f;
					t.z = -addPos.z;
					D3DXVec3Normalize(&t, &addPos);
					//半径分押し戻す。
					t *= m_radius;
					addPos += t;
					//続いて壁に沿って滑らせる。
					//滑らせる方向を計算。
					D3DXVec3Cross(&t, &callback.hitNormalXZ, &CVec3Up);
					D3DXVec3Normalize(&t, &addPos);
					t *= (D3DXVec3Dot(&t, &addPosXZ));
					addPos += t;	//滑らせるベクトルを加算。
				}
				else {
					//どことも当たらないので終わり。
					break;
				}
				loopCount++;
				if (loopCount == 5) {
					break;
				}
			}
		}
		//下方向を調べる。
		{
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			start.setOrigin(btVector3(m_transform.position.x, m_transform.position.y, m_transform.position.z));
			D3DXVECTOR3 newPos;
			SweepResultGround callback;
			if (fabsf(addPos.y) > 0.0001f) {
				newPos = m_transform.position;
				newPos.y += addPos.y;

				end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

				g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
			}
			if (callback.isHit) {
				//当たった。
				//地面。
				m_moveSpeed.y = 0.0f;
				addPos.y = callback.hitPos.y - m_transform.position.y;
				addPos.y += m_radius;
			}
		}
		m_transform.position += (addPos);

		const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();

		m_rigidBody->getWorldTransform().setOrigin(btVector3(m_transform.position.x, m_transform.position.y, m_transform.position.z));
	}

	isTurn = false;

	if (m_pInput->IsPressShift() && m_pInput->IsTriggerUp()){
		m_moveSpeed.y = 10.0f;
	}
	else if (m_pInput->IsPressUp()){
		m_transform.position.z +=0.1f;
		isTurn = true;
		//180度向かせる。
		g_targetAngleY = D3DXToRadian(180.0f);
	}
	if (m_pInput->IsPressDown()){
		m_transform.position.z -= 0.1f;
		isTurn = true;
		//正面を向かせる。
		g_targetAngleY = D3DXToRadian(0.0f);
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressRight()){
		m_transform.angle.y -= 0.1f;
	}
	else if (m_pInput->IsPressRight()){
		m_transform.position.x += 0.1f;
		isTurn = true;
		//右方向を向かせる。
		g_targetAngleY = D3DXToRadian(-90.0f);
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressLeft()){
		m_transform.angle.y += 0.1f;
	}
	else if (m_pInput->IsPressLeft()){
		m_transform.position.x -= 0.1f;
		isTurn = true;
		//左方向を向かせる
		g_targetAngleY = D3DXToRadian(90.0f);
	}
	static const float fPI = 3.14159265358979323846f;
	if (isTurn) {
		float angleDiff = g_targetAngleY - g_currentAngleY;	//目的角度までどれだけ回せがいいのかを計算する。
		float angleDiffAbs = fabsf(angleDiff);				//回す角度の絶対値を計算。
		if (angleDiffAbs > 0.0001f) {						//回す角度の大きさが非常に小さい場合は回さない。
			float turnDir = angleDiff / angleDiffAbs;		//回転させる方向を計算する。
			if (angleDiffAbs >  fPI) {						//回転させる角度が180度を越えているかを判定する。
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
	SetRotation(D3DXVECTOR3(0.0f, 1.0f, 0.0f), g_currentAngleY);
	C3DImage::Update();
	SINSTANCE(CShadowRender)->SetObjectPos(m_transform.position);
	SINSTANCE(CShadowRender)->SetShadowCameraPos(m_transform.position + D3DXVECTOR3(0.0f, 10.0f, 0.0f));
}

void CPlayer::Draw(){
	IMAGE3D* img = GetImage();
	LPD3DXMESH mesh = img->pModel->GetContainer()->MeshData.pMesh;
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
	SINSTANCE(CRenderContext)->SetCurrentLight(&m_light);
	C3DImage::Draw();
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
	SetUpLight();
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
}