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
			//�����B
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;
		hitPointNormal.x = convexResult.m_hitNormalLocal.x();
		hitPointNormal.y = convexResult.m_hitNormalLocal.y();
		hitPointNormal.z = convexResult.m_hitNormalLocal.z();
		float d = D3DXVec3Dot(&hitPointNormal, &CVec3Up);
		if (d < 0.0f) {
			//�������ĂȂ��B
			return 0.0f;
		}
		if (acosf(d) > fPI * 0.2) {
			//�z���g�͒n�ʂ��ǂ����Ƃ��̑���������̂��x�X�g�Ȃ񂾂��ǁA����͊p�x�ŁB
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
			//�����B
			return 0.0f;
		}

		D3DXVECTOR3 hitPointNormal;
		hitPointNormal.x = convexResult.m_hitNormalLocal.x();
		hitPointNormal.y = convexResult.m_hitNormalLocal.y();
		hitPointNormal.z = convexResult.m_hitNormalLocal.z();

		float d = D3DXVec3Dot(&hitPointNormal, &CVec3Up);
		if (acosf(d) < fPI * 0.2) {
			//�z���g�͒n�ʂ��ǂ����Ƃ��̑���������̂��x�X�g�Ȃ񂾂��ǁA����͊p�x�ŁB
			return 0.0f;
		}
		isHit = true;
		//XZ���ʂł̖@���B
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

//����(�����蔻��̂��镨��)�̏�����
void CIsIntersect::CollisitionInitialize(D3DXVECTOR3* position,float radius)
{
	//�R���W�����������B
	m_radius = radius;
	//Box(������),sphere(����)�Ȃǂœ�����͈͂����߂�B
	m_collisionShape = new btSphereShape(m_radius);//�����ō��̂̌`�������
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
	//���[���h�ɒǉ��B
	g_bulletPhysics.AddRigidBody(m_rigidBody);
}

//�����G���W�����g���������蔻�菈��&�W�����v����
void CIsIntersect::Intersect(D3DXVECTOR3* position, D3DXVECTOR3* moveSpeed)
{

	static float deltaTime = 1.0f / 60.0f;						/************/
	static D3DXVECTOR3 gravity(0.0f, -40.0f, 0.0f);	//�d��		/*  �W		*/
	D3DXVECTOR3 addGravity = gravity;							/*  ��		*/
	addGravity *= (deltaTime);			//0.16�b���ɉ���		/*  ��		*/
	*moveSpeed += (addGravity);	//�������x					/*  �v		*/
	D3DXVECTOR3 addPos;											/*  ��		*/
	addPos = *moveSpeed;										/*  ��		*/
	addPos *= (deltaTime);										/*			*/
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);							/************/

	//XZ���ʂ𒲂ׂ�B
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
				//���������B
				//�ǁB
				addPos.x = callback.hitPos.x - position->x;
				addPos.z = callback.hitPos.z - position->z;

				D3DXVECTOR3 t;
				t.x = -addPos.x;
				t.y = 0.0f;
				t.z = -addPos.z;
				D3DXVec3Normalize(&t, &t);
				//D3DXVec3Normalize(&t, &addPos);
				//���a�������߂��B
				t *= m_radius;
				addPos += t;
				//�����ĕǂɉ����Ċ��点��B
				//���点��������v�Z�B
				D3DXVec3Cross(&t, &callback.hitNormalXZ, &Up);
				D3DXVec3Normalize(&t, &t);
				//D3DXVec3Normalize(&t, &addPos);
				t *= D3DXVec3Dot(&t, &addPosXZ);
				addPos += t;	//���点��x�N�g�������Z�B
			}
			else {
				//�ǂ��Ƃ�������Ȃ��̂ŏI���B
				break;
			}
			loopCount++;
			if (loopCount == 5) {
				break;
			}
		}
	}
	//�������𒲂ׂ�B
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
			//���������B
			//�n�ʁB
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
	static D3DXVECTOR3 gravity(0.0f, -40.0f, 0.0f);	//�d��		/*  �W		*/
	D3DXVECTOR3 addGravity = gravity;							/*  ��		*/
	addGravity *= (deltaTime);			//0.16�b���ɉ���		/*  ��		*/
	*moveSpeed += (addGravity);	//�������x						/*  �v		*/
	D3DXVECTOR3 addPos;											/*  ��		*/
	addPos = *moveSpeed;										/*  ��		*/
	addPos *= (deltaTime);										/*			*/
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);							/************/

	//XZ���ʂ𒲂ׂ�B
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
				//���������B
				//�ǁB
				addPos.x = callback.hitPos.x - position->x;
				addPos.z = callback.hitPos.z - position->z;

				D3DXVECTOR3 t;
				t.x = -addPos.x;
				t.y = 0.0f;
				t.z = -addPos.z;
				D3DXVec3Normalize(&t, &t);
				//D3DXVec3Normalize(&t, &addPos);
				//���a�������߂��B
				t *= m_radius;
				addPos += t;
				//�����ĕǂɉ����Ċ��点��B
				//���点��������v�Z�B
				D3DXVec3Cross(&t, &callback.hitNormalXZ, &Up);
				D3DXVec3Normalize(&t, &t);
				//D3DXVec3Normalize(&t, &addPos);
				t *= D3DXVec3Dot(&t, &addPosXZ);
				addPos += t;	//���点��x�N�g�������Z�B
			}
			else {
				//�ǂ��Ƃ�������Ȃ��̂ŏI���B
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