#include "stdafx.h"
#include "Block.h"
#include "ShadowRender.h"

void CBlock::OnDestroy(){
	g_bulletPhysics.RemoveRigidBody(m_rigidBody);
	//子供に死亡したことを通知。
	if (m_child){
		m_child->OnDestroyParent();
	}
	m_isDead = true;
}


//親が死んだときに呼ばれる処理。
void CBlock::OnDestroyParent()
{
	m_eState = enState_Fall;
	m_fallPosY = m_parent->GetPos().y;
	SetParent(m_parent->m_parent);
	//自分の子供を落下させる。
	CBlock* child = m_child;
	while (child != NULL){
		child->m_fallPosY = child->m_parent->GetPos().y;
		child->m_eState = enState_Fall;
		child = child->m_child;
	}
}


void CBlock::Initialize(D3DXVECTOR3 pos)
{
	strcpy(m_pFileName, "image/BR.x");
	C3DImage::Initialize();
	m_transform.position = pos; //D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	SetRotation(D3DXVECTOR3(0, 0, 0), 0.1f);
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_RigitBody.Initialize(&m_transform.position, &m_transform.scale);
	

	this->Build(D3DXVECTOR3(1.0f, 1.0f, 1.0f), m_transform.position);

	m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
	//m_moveSpeed.x = 0.0f;
	//m_moveSpeed.z = 0.0f;
	//m_moveSpeed.y = 0.0f;

	//m_radius = 1.0f;

	SetAlive(true);

	//SetAlpha(1.0f);
	//m_IsIntersect.CollisitionInitialize(&m_transform.position, m_radius);

	C3DImage::SetImage();
}


void CBlock::Update()
{
	switch (m_eState){
	case enState_Normal:{
		//物理エンジンで計算された剛体の位置と回転を反映させる。
		//const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();
		//const btQuaternion& rRot = m_rigidBody->getWorldTransform().getRotation();
		//D3DXVECTOR3 pos(rPos.x(), rPos.y(), rPos.z());
		//D3DXQUATERNION rot(rRot.x(), rRot.y(), rRot.z(), rRot.w());
		//m_transform.position.x = rPos.x();
		//m_transform.position.y = rPos.y();
		//m_transform.position.z = rPos.z();
		//m_box.SetPosition(pos);
		//m_box.SetRotation(rot);
		//m_box.UpdateWorldMatrix();
		//m_shadowModel.SetWorldMatrix(m_box.GetWorldMatrix());
		//ShadowMap().Entry(&m_shadowModel);
		//m_life += 1.0f / 60.0f;
		////m_transform.position.y -= 0.05f;

		//btVector3 a(0.0f, 0.0f, 1.0f);

		//if (GetAsyncKeyState('A')){
		//	m_rigidBody->setLinearVelocity(a);
		//}
		m_rigidBody->getWorldTransform().setOrigin(btVector3(m_transform.position.x, m_transform.position.y, m_transform.position.z));
	}break;
	case enState_Broken:{
	}break;
	case enState_Fall:{
		m_transform.position.y -= 0.1f;
		if (m_fallPosY > m_transform.position.y){
			m_transform.position.y = m_fallPosY;
			m_eState = enState_Normal;
		}
	}break;
	}
	

	C3DImage::Update();
}


void CBlock::Draw()
{
	SetUpTechnique();
	C3DImage::Draw();
}


void CBlock::Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos)
{

	//この引数に渡すのはボックスhalfsizeなので、0.5倍する。
	m_collisionShape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	float mass = 0.0f;

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	//m_rigidBody->setUserIndex(1);
	//ワールドに追加。
	g_bulletPhysics.AddRigidBody(m_rigidBody);
}