#include "Bullet.h"

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	C3DImage::Initialize();
	m_transform.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetRotation(D3DXVECTOR3(0, 0, 1), 0.0f);//’e‚ªZŽ²‰ñ“]‚·‚é
	m_transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetAlive(true);
	SetAlpha(1.0f);//“§–¾“x
	Shotflag = false;
	m_radius = 1.0f;
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;
	this->Build();
	m_IsIntersect.CollisitionInitialize(&m_transform.position, m_radius);
	C3DImage::SetImage();
}

void Bullet::Update()
{
	CPlayer* m_Player = (SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D")));
	Shotflag = m_Player->GetShotflag();

	if (Shotflag==false)
	{
		m_transform.position = m_Player->GetPos();
	}
	
	if (Shotflag)
	{
		m_moveSpeed.z = 100.0f;
	}	
	m_IsIntersect.Intersect(&m_transform.position, &m_moveSpeed);
	C3DImage::Update();
}

void Bullet::Draw()
{
	if (Shotflag)
	{
		SetUpTechnique();
		C3DImage::Draw();
	}
}
void Bullet::OnDestroy()
{
	m_Rigidbody.OnDestroy();
}

void Bullet::Build()
{
	m_Rigidbody.Build(m_transform.scale, m_transform.position);
}
