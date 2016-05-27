#include "stdafx.h"
#include "islntersect.h"
#include "CBManager.h"
#include "CollisionType.h"

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
		if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Player 
			|| convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Chocoball
			|| convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_ChocoballTrigger) {
			//無視。
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;
		hitPointNormal.x = convexResult.m_hitNormalLocal.x();
		hitPointNormal.y = convexResult.m_hitNormalLocal.y();
		hitPointNormal.z = convexResult.m_hitNormalLocal.z();
		float d = D3DXVec3Dot(&hitPointNormal, &CVec3Up);
		if (d < 0.0f) {
			//当たってない。
			return 0.0f;
		}
		if (acosf(d) > fPI * 0.2) {
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
		if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_ChocoballTrigger) {
			CCBManager* mgr = (CCBManager*)convexResult.m_hitCollisionObject->getUserPointer();
			if (!mgr->GetAlive()){
				SINSTANCE(CObjectManager)->AddObject(mgr, _T("CHOCO"), PRIORTY::OBJECT3D, false);
				mgr->Initialize();
				g_bulletPhysics.RemoveCollisionObject((btGhostObject*)convexResult.m_hitCollisionObject);
				g_player->SetCBM(mgr);
			}
			return 0.0f;
		}

		if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Player
			|| convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Chocoball) {
			//無視。
			return 0.0f;
		}

		D3DXVECTOR3 hitPointNormal;
		hitPointNormal.x = convexResult.m_hitNormalLocal.x();
		hitPointNormal.y = convexResult.m_hitNormalLocal.y();
		hitPointNormal.z = convexResult.m_hitNormalLocal.z();

		float d = D3DXVec3Dot(&hitPointNormal, &CVec3Up);
		if (acosf(d) < fPI * 0.2) {
			//ホントは地面かどうかとかの属性を見るのがベストなんだけど、今回は角度で。
			return 0.0f;
		}
		isHit = true;
		//XZ平面での法線。
		hitNormalXZ.x = hitPointNormal.x;
		hitNormalXZ.y = 0.0f;
		hitNormalXZ.z = hitPointNormal.z;
		D3DXVec3Normalize(&hitNormalXZ, &hitNormalXZ);

		btTransform transform = convexResult.m_hitCollisionObject->getWorldTransform();


		hitPos.x = convexResult.m_hitPointLocal.x();
		hitPos.y = convexResult.m_hitPointLocal.y();
		hitPos.z = convexResult.m_hitPointLocal.z();
		return 0.0f;
	}
};

CIsIntersect::CIsIntersect()
{
}

CIsIntersect::~CIsIntersect()
{
}

//剛体(当たり判定のある物体)の初期化
void CIsIntersect::CollisitionInitialize(D3DXVECTOR3* position,float radius)
{
	//コリジョン初期化。
	m_radius = radius;
	//Box(立方体),sphere(球体)などで当たり範囲を決める。
	m_collisionShape = new btSphereShape(m_radius);//ここで剛体の形状を決定
	/*(btVector3(m_radius, m_radius, );*/


	float mass = 0.0f;

	btTransform rbTransform;
	rbTransform.setIdentity();
	rbTransform.setOrigin(btVector3(position->x, position->y, position->z));
	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(rbTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserIndex(CollisionType_Player);
	//ワールドに追加。
	g_bulletPhysics.AddRigidBody(m_rigidBody);
}

//物理エンジンを使った当たり判定処理&ジャンプ処理
void CIsIntersect::Intersect(D3DXVECTOR3* position, D3DXVECTOR3* moveSpeed)
{

	static float deltaTime = 1.0f / 60.0f;						/************/
	static D3DXVECTOR3 gravity(0.0f, -40.0f, 0.0f);	//重力		/*  ジ		*/
	D3DXVECTOR3 addGravity = gravity;							/*  ャ		*/
	addGravity *= (deltaTime);			//0.16秒事に加速		/*  ン		*/
	*moveSpeed += (addGravity);	//落下速度					/*  プ		*/
	D3DXVECTOR3 addPos;											/*  処		*/
	addPos = *moveSpeed;										/*  理		*/
	addPos *= (deltaTime);										/*			*/
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);							/************/

	//XZ平面を調べる。
	{
		int loopCount = 0;
		while (true) {
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			start.setOrigin(btVector3(position->x, position->y, position->z));
			D3DXVECTOR3 newPos;
			SweepResultWall callback;
			D3DXVECTOR3 addPosXZ = addPos;
			addPosXZ.y = 0.0f;
			if (D3DXVec3Length(&addPosXZ) > 0.0001f) {
				newPos = (*position + addPosXZ);
				end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
				g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
			}
			if (callback.isHit) {
				//当たった。
				//壁。
				addPos.x = callback.hitPos.x - position->x;
				addPos.z = callback.hitPos.z - position->z;

				D3DXVECTOR3 t;
				t.x = -addPos.x;
				t.y = 0.0f;
				t.z = -addPos.z;
				D3DXVec3Normalize(&t, &t);
				//D3DXVec3Normalize(&t, &addPos);
				//半径分押し戻す。
				t *= m_radius;
				addPos += t;
				//続いて壁に沿って滑らせる。
				//滑らせる方向を計算。
				D3DXVec3Cross(&t, &callback.hitNormalXZ, &Up);
				D3DXVec3Normalize(&t, &t);
				//D3DXVec3Normalize(&t, &addPos);
				t *= D3DXVec3Dot(&t, &addPosXZ);
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
		start.setOrigin(btVector3(position->x, position->y, position->z));
		D3DXVECTOR3 newPos;
		SweepResultGround callback;
		if (fabsf(addPos.y) > 0.0001f) {
			newPos = *position;
			newPos.y += addPos.y;


			end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

			g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
		}
		if (callback.isHit) {
			//当たった。
			//地面。
			moveSpeed->y = 0.0f;
			addPos.y = callback.hitPos.y - position->y;
			addPos.y += m_radius;
		}
	}

	*position += addPos;

	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();

	m_rigidBody->getWorldTransform().setOrigin(btVector3(position->x, position->y, position->z));
}

void CIsIntersect::Intersect2(D3DXVECTOR3* position, D3DXVECTOR3* moveSpeed)
{

	static float deltaTime = 1.0f / 60.0f;						/************/
	static D3DXVECTOR3 gravity(0.0f, -40.0f, 0.0f);	//重力		/*  ジ		*/
	D3DXVECTOR3 addGravity = gravity;							/*  ャ		*/
	addGravity *= (deltaTime);			//0.16秒事に加速		/*  ン		*/
	*moveSpeed += (addGravity);	//落下速度						/*  プ		*/
	D3DXVECTOR3 addPos;											/*  処		*/
	addPos = *moveSpeed;										/*  理		*/
	addPos *= (deltaTime);										/*			*/
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);							/************/

	//XZ平面を調べる。
	{
		int loopCount = 0;
		while (true) {
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			start.setOrigin(btVector3(position->x, position->y, position->z));
			D3DXVECTOR3 newPos;
			SweepResultWall callback;
			D3DXVECTOR3 addPosXZ = addPos;
			addPosXZ.y = 0.0f;
			if (D3DXVec3Length(&addPosXZ) > 0.0001f) {
				newPos = (*position + addPosXZ);
				end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
				g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
			}
			if (callback.isHit) {
				//当たった。
				//壁。
				addPos.x = callback.hitPos.x - position->x;
				addPos.z = callback.hitPos.z - position->z;

				D3DXVECTOR3 t;
				t.x = -addPos.x;
				t.y = 0.0f;
				t.z = -addPos.z;
				D3DXVec3Normalize(&t, &t);
				//D3DXVec3Normalize(&t, &addPos);
				//半径分押し戻す。
				t *= m_radius;
				addPos += t;
				//続いて壁に沿って滑らせる。
				//滑らせる方向を計算。
				D3DXVec3Cross(&t, &callback.hitNormalXZ, &Up);
				D3DXVec3Normalize(&t, &t);
				//D3DXVec3Normalize(&t, &addPos);
				t *= D3DXVec3Dot(&t, &addPosXZ);
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
	
	*position += addPos;

	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();

	m_rigidBody->getWorldTransform().setOrigin(btVector3(position->x, position->y, position->z));
}