#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "ShadowRender.h"

CPlayer::CPlayer()
{
	strcpy(m_pFileName, "image/TestPlayer.x");
}

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
	m_transform.position = D3DXVECTOR3(0, 1.0f, -17);
	m_transform.angle = D3DXVECTOR3(0, 0, 0);
	m_transform.scale = D3DXVECTOR3(1, 1, 1);
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	m_radius = 1.0f;

	SetAlive(true);

	SetAlpha(0.5f);

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

void CPlayer::Initialize(float x,float y)
{
	C3DImage::Initialize();
	m_transform.position = D3DXVECTOR3(x, y,-18);
	m_transform.angle = D3DXVECTOR3(2,1,0);
	m_transform.scale = D3DXVECTOR3(1,1,1);
	SetAlive(true);
	m_OriginalInit = true;
	
	C3DImage::SetImage();
}

void CPlayer::Update()
{
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


	if (m_pInput->IsPressShift() && m_pInput->IsPressUp()){
		m_moveSpeed.y = 5.5f;
		//m_transform.position.y += 0.05f;
	}
	else if (m_pInput->IsPressUp()){
		m_transform.position.z +=0.05f;
		m_transform.angle.y = D3DXToRadian(180);;
	}
	if (m_pInput->IsPressDown()){
		m_transform.position.z -= 0.05f;
		m_transform.angle.y = D3DXToRadian(0);
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressRight()){
		m_transform.angle.y -= 0.05f;
	}
	else if (m_pInput->IsPressRight()){
		m_transform.position.x += 0.05f;
		m_transform.angle.y = D3DXToRadian(-90);
	}
	if (m_pInput->IsPressShift() && m_pInput->IsPressLeft()){
		m_transform.angle.y += 0.05f;
	}
	else if (m_pInput->IsPressLeft()){
		m_transform.position.x -= 0.05f;
		m_transform.angle.y = D3DXToRadian(90);;
	}
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