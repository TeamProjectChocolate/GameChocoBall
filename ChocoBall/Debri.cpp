#include "stdafx.h"
#include "Debri.h"
#include "BulletPhysics.h"

void CDebri::Initialize()
{
	C3DImage::Initialize();
	strcpy(m_pFileName, "image/Debri.x");
	m_transform.position = D3DXVECTOR3(0, 10, -17);
	m_transform.angle = D3DXVECTOR3(0, 0, 0);
	m_transform.scale = D3DXVECTOR3(0.1f,0.1f,0.1f);
	m_life = 0.0f;
	SetAlive(true);
	this->Build(D3DXVECTOR3(1.4f, 1.4f, 1.4f), m_transform.position);
	C3DImage::SetImage();
}
void CDebri::Update()
{
	//物理エンジンで計算された剛体の位置と回転を反映させる。
	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();
	const btQuaternion& rRot = m_rigidBody->getWorldTransform().getRotation();
	D3DXVECTOR3 pos(rPos.x(), rPos.y(), rPos.z());
	D3DXQUATERNION rot(rRot.x(), rRot.y(), rRot.z(), rRot.w());
	m_transform.position.x = rPos.x();
	m_transform.position.y = rPos.y();
	m_transform.position.z = rPos.z();
	/*m_box.SetPosition(pos);
	m_box.SetRotation(rot);
	m_box.UpdateWorldMatrix();
	m_shadowModel.SetWorldMatrix(m_box.GetWorldMatrix());
	ShadowMap().Entry(&m_shadowModel);*/
	//m_life += 1.0f / 60.0f;
	C3DImage::Update();
}
void CDebri::Draw()
{
	C3DImage::Draw();
}
void CDebri::OnDestroy()
{
	g_bulletPhysics.RemoveRigidBody(m_rigidBody);
	delete m_myMotionState;
	delete m_collisionShape;
	delete m_rigidBody;
}
/*!
*@brief	構築処理。
*@param[in]	size	箱のサイズ。
*@param[in]	pos		箱の座標。
*/
void CDebri::Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos)
{
	//この引数に渡すのはボックスhalfsizeなので、0.5倍する。
	m_collisionShape = new btBoxShape(btVector3(size.x*0.5f, size.y*0.5f, size.z*0.5f));
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));
	float mass = 1.0f;

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserIndex(1);
	//ワールドに追加。
	g_bulletPhysics.AddRigidBody(m_rigidBody);

}
