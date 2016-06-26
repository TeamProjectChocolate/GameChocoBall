#include "stdafx.h"
#include "EnemyBase.h"
#include "islntersect.h"
#include "EnemyManager.h"

void EnemyBase::Build(){
	m_pEnemyManager = SINSTANCE(CObjectManager)->FindGameObject<CEnemyManager>(_T("EnemyManager"));
}

void EnemyBase::Update(){
	if (m_IsHit){
		RollingEnemy();
	}

	C3DImage::Update();
}

void EnemyBase::OnDestroy()
{
	SetAlive(false);
}

void EnemyBase::PlayerBulletHit(D3DXVECTOR3 moveDir)
{
	m_IsIntersect.CollisitionInitialize(&m_transform.position, 1.0f, CollisionType_Enemy);
	m_IsHit = true;
	btRigidBody* rb = m_IsIntersect.GetRigidBody();//�G�l�~�[�̍��̂��擾
	//m_IsIntersect.GetSphereShape()->setLocalScaling(btVector3(0.3f, 0.3f, 0.3f));//�G�l�~�[�̋����������ݒ肵�A�`���R�{�[���ɖ������悤�ɂ��Ă���B
	rb->setMassProps(1.0f, btVector3(0.01f, 0.01f, 0.01f));//�������͎��ʁA�������͉�]�̂��₷��
	moveDir *= 750.0f;
	rb->applyForce(btVector3(moveDir.x, moveDir.y + 1000.0f, moveDir.z), btVector3(1.0f, 1.0f, 1.0f));//�`���R�{�[���ɓ������Đ�����ԗ͂�ݒ�
	rb->setAngularVelocity(btVector3(5.0f, 5.0f, 5.0f));
	m_animation.SetAnimSpeed(2.0f);//�A�j���[�V�����Đ����x��ݒ�
}

void EnemyBase::RollingEnemy()
{
	btRigidBody* rb = m_IsIntersect.GetRigidBody();//�G�l�~�[�̍��̂��擾

	//�����G���W���Ōv�Z�����ړ����G�l�~�[�ɔ��f
	btVector3 pos = rb->getWorldTransform().getOrigin();
	m_transform.position.x = pos.x();
	m_transform.position.y = pos.y();
	m_transform.position.z = pos.z();

	//�����G���W���Ōv�Z������]���G�l�~�[�ɔ��f
	btQuaternion rot = rb->getWorldTransform().getRotation();
	m_transform.angle.x = rot.x();
	m_transform.angle.y = rot.y();
	m_transform.angle.z = rot.z();
	m_transform.angle.w = rot.w();

	//���S�܂ł̑ҋ@���Ԃ̐ݒ�
	m_deadTimer += 1.0 / 60.0f;
	if (m_deadTimer >= 2.0f){
		m_pEnemyManager->DeleteEnemy(this);
	}
}
