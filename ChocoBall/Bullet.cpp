#include "stdafx.h"
#include "Bullet.h"

Bullet::~Bullet()
{

}

void Bullet::Initialize()
{
	C3DImage::Initialize();
	m_transform.position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	SetRotation(D3DXVECTOR3(0, 0, 1), 0.0f);//弾がZ軸回転する
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetAlive(true);
	SetAlpha(1.0f);//透明度
	//Shotflag = false;
	//m_Hitflag = false;
	m_radius = 1.0f;
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;
	this->Build();
	m_IsIntersect.CollisitionInitialize(&m_transform.position, m_radius);
	//m_pPlayer = (SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D")));
	C3DImage::SetImage();
}

void Bullet::Update()
{
	//プレイヤーの向いているベクトルを弾に加算
	m_transform.position.x = m_transform.position.x + m_dir.x*m_Speed;
	m_transform.position.y = m_transform.position.y + m_dir.y*m_Speed;
	m_transform.position.z = m_transform.position.z + m_dir.z*m_Speed;


	m_IsIntersect.Intersect2(&m_transform.position, &m_moveSpeed);
	C3DImage::Update();
}
void Bullet::Draw()
{
	SetUpTechnique();
	C3DImage::Draw();
}

void Bullet::OnDestroy()
{

}

void Bullet::Build()
{

}
