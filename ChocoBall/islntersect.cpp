#pragma once

#include "stdafx.h"
#include "islntersect.h"
#include "CBManager.h"
#include "CollisionType.h"

#define ORIGIN_CENTER	//��`�ŋN�_�������B
void GenelateChocoBall(CCBManager* mgr, btGhostObject* m_hitCollisionObject,CAudio* pAudio);

// �v���C���[�p�R�[���o�b�N
struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	D3DXVECTOR3 hitPos;
	D3DXVECTOR3 startPos;
	float fMin;

	SweepResultGround()
	{
		isHit = false;
		fMin = FLT_MAX;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_ChocoballTrigger) {

			CCBManager* mgr = (CCBManager*)convexResult.m_hitCollisionObject->getUserPointer();
			GenelateChocoBall(mgr, (btGhostObject*)convexResult.m_hitCollisionObject,m_pAudio);
			return 0.0f;
		}

		if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Player 
			|| convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Chocoball
			|| convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Enemy) {
			//�����B
			return 0.0f;
		}
		else if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Camera) {
			//�����B
			return 0.0f;
		}
		else if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Bullet){
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
		D3DXVECTOR3 hitPosTmp;
		hitPosTmp.x = convexResult.m_hitPointLocal.x();
		hitPosTmp.y = convexResult.m_hitPointLocal.y();
		hitPosTmp.z = convexResult.m_hitPointLocal.z();
		D3DXVECTOR3 diff;
		diff = hitPosTmp - startPos;
		float len = D3DXVec3Length(&diff);
		if (len < fMin){
			hitPos = hitPosTmp;
			fMin = len;
		}
		return 0.0f;
	}
	CAudio* m_pAudio;
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
			GenelateChocoBall(mgr, (btGhostObject*)convexResult.m_hitCollisionObject,m_pAudio);
			return 0.0f;
		}

		if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Player
			|| convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Chocoball
			|| convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Enemy)
		{
			//�����B
			return 0.0f;
		}
		else if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Camera) {
			//�����B
			return 0.0f;
		}
		else if (convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Bullet){
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
	CAudio* m_pAudio;
};


void GenelateChocoBall(CCBManager* mgr, btGhostObject* m_hitCollisionObject,CAudio* pAudio){
	if (!mgr->GetAlive()){
		pAudio->PlayCue("Chocoball", true,nullptr);//�`���R����Audio
		mgr->Initialize();
		mgr->SetAlive(true);
		SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->RemoveCollisionObject(m_hitCollisionObject);
		g_player->SetCBM(mgr);
	}
}

// �J�����p�R�[���o�b�N
struct SweepResultGround_Camera : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	D3DXVECTOR3 hitPos;
	D3DXVECTOR3 startPos;
	float fMin;

	SweepResultGround_Camera()
	{
		isHit = false;
		fMin = FLT_MAX;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != CollisionType_Map
			|| convexResult.m_hitCollisionObject->getUserIndex() == CollisionType_Enemy)
		{
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
		D3DXVECTOR3 hitPosTmp;
		hitPosTmp.x = convexResult.m_hitPointLocal.x();
		hitPosTmp.y = convexResult.m_hitPointLocal.y();
		hitPosTmp.z = convexResult.m_hitPointLocal.z();
		D3DXVECTOR3 diff;
		diff = hitPosTmp - startPos;
		float len = D3DXVec3Length(&diff);
		if (len < fMin){
			hitPos = hitPosTmp;
			fMin = len;
		}
		return 0.0f;
	}
};

CIsIntersect::CIsIntersect()
{
	m_isHitGround = false;
	m_Jumpflag = false;
}

CIsIntersect::~CIsIntersect()
{
}

//����(�����蔻��̂��镨��)�̏�����
void CIsIntersect::CollisitionInitialize(D3DXVECTOR3* position,float radius,CollisionType type)
{
	//�R���W�����������B
	m_radius = radius;
	//Box(������),sphere(����)�Ȃǂœ�����͈͂����߂�B
	m_collisionShape = new btSphereShape(m_radius);//�����ō��̂̌`�������

	float mass = 0.1f;

	btTransform rbTransform;
	rbTransform.setIdentity();
	rbTransform.setOrigin(btVector3(position->x, position->y, position->z));
	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(rbTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserIndex(type);
	//���[���h�ɒǉ��B
	SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->AddRigidBody(m_rigidBody);
}

bool CIsIntersect::IsHitGround()
{
	return m_isHitGround;
}
//�����G���W�����g���������蔻�菈��&�W�����v����
void CIsIntersect::Intersect(D3DXVECTOR3* position, D3DXVECTOR3* moveSpeed,bool Jumpflag)
{
	m_isHitGround = false;
	m_Jumpflag = Jumpflag;
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
			callback.m_pAudio = m_pAudio;
			D3DXVECTOR3 addPosXZ = addPos;
			addPosXZ.y = 0.0f;
			if (D3DXVec3Length(&addPosXZ) > 0.0001f) {
				newPos = (*position + addPosXZ);
				end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
				SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->ConvexSweepTest(m_collisionShape, start, end, callback);
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
#ifdef ORIGIN_CENTER
		start.setOrigin(btVector3(position->x, position->y, position->z));
#else
		start.setOrigin(btVector3(position->x, position->y + m_radius, position->z));
#endif
		D3DXVECTOR3 newPos;
		SweepResultGround callback;
		callback.m_pAudio = m_pAudio;
		callback.startPos = *position;
		if (fabsf(addPos.y) > 0.0001f) {
			newPos = *position;
#ifdef ORIGIN_CENTER
			newPos.y += addPos.y;
#else
			newPos.y += addPos.y + m_radius;
#endif
			if (m_Jumpflag)
			{
				//�W�����v��
				end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
			}
			else
			{
				//�W�����v���ȊO�͒n�ʂɃv���C���[�������t����
				end.setOrigin(btVector3(newPos.x, newPos.y - 1.0f, newPos.z));
			}

			SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->ConvexSweepTest(m_collisionShape, start, end, callback);
		}
		if (callback.isHit) {
			//���������B
			//�n�ʁB
			
			D3DXVECTOR3 Circle;
			float x = 0.0f;
			float offset = 0.0f;	//�����߂��ʁB
			Circle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			
			Circle = *position;
			Circle.y = callback.hitPos.y;//�~�̒��S
			D3DXVECTOR3 v = Circle - callback.hitPos;
			x = D3DXVec3Length(&v);//���̂̊p�ƃv���C���[�̊Ԃ̉����̋��������܂�B

			offset = sqrt(m_radius*m_radius - x*x);//y�̕����������߂�B
		
			moveSpeed->y = 0.0f;
			addPos.y = callback.hitPos.y - position->y;
			m_isHitGround = true;
#ifdef ORIGIN_CENTER
			addPos.y += offset;
			
#endif
		}
		
	}

	*position += addPos;

	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();

	m_rigidBody->getWorldTransform().setOrigin(btVector3(position->x, position->y, position->z));
}

void CIsIntersect::Intersect2(D3DXVECTOR3* position, D3DXVECTOR3* moveSpeed)
{

	static float deltaTime = 1.0f / 60.0f;						/************/
	static D3DXVECTOR3 gravity(0.0f, 0.0f, 0.0f);	//�d��		/*  �W		*/
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
			callback.m_pAudio = m_pAudio;
			D3DXVECTOR3 addPosXZ = addPos;
			addPosXZ.y = 0.0f;
			if (D3DXVec3Length(&addPosXZ) > 0.0001f) {
				newPos = (*position + addPosXZ);
				end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
				SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->ConvexSweepTest(m_collisionShape, start, end, callback);
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

void CIsIntersect::IntersectCamera(D3DXVECTOR3* position,D3DXVECTOR3* moveSpeed)
{
	D3DXVECTOR3 addPos = *moveSpeed;
	//�������𒲂ׂ�B
	{
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
#ifdef ORIGIN_CENTER
		start.setOrigin(btVector3(position->x, position->y, position->z));
#else
		start.setOrigin(btVector3(position->x, position->y + m_radius, position->z));
#endif
		D3DXVECTOR3 newPos;
		SweepResultGround_Camera callback;
		callback.startPos = *position;
		if (fabsf(addPos.y) > 0.0001f) {
			newPos = *position;
#ifdef ORIGIN_CENTER
			newPos.y += addPos.y;
#else
			newPos.y += addPos.y + m_radius;
#endif
			end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
			SINSTANCE(CObjectManager)->FindGameObject<CBulletPhysics>(_T("BulletPhysics"))->ConvexSweepTest(m_collisionShape, start, end, callback);
		}
		if (callback.isHit) {
			//���������B
			//�n�ʁB

			D3DXVECTOR3 Circle;
			float x = 0.0f;
			float offset = 0.0f;	//�����߂��ʁB
			Circle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			Circle = *position;
			Circle.y = callback.hitPos.y;//�~�̒��S
			D3DXVECTOR3 v = Circle - callback.hitPos;
			x = D3DXVec3Length(&v);//���̂̊p�ƃv���C���[�̊Ԃ̉����̋��������܂�B

			offset = sqrt(m_radius*m_radius - x*x);//y�̕����������߂�B

			moveSpeed->y = 0.0f;
			addPos.y = callback.hitPos.y - position->y;
#ifdef ORIGIN_CENTER
			addPos.y += offset;
#endif
		}

	}
	*position += addPos;

	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();

	m_rigidBody->getWorldTransform().setOrigin(btVector3(position->x, position->y, position->z));
}