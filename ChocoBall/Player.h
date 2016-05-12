#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "DirectInput.h"
#include "BulletPhysics.h"
#include "Light.h"


const float	g_cTurnSpeed = D3DXToRadian(10.0f);
static const float fPI = 3.14159265358979323846f;

class CPlayer : public C3DImage
{
public:
	CPlayer(){
		m_pInput = nullptr;
		m_ghostObject = nullptr;
		m_collisionShape = nullptr;
		m_rigidBody = nullptr;
		m_myMotionState = nullptr;
		strcpy(m_pFileName, "image/TestPlayer.x");
	};
	~CPlayer();

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void ConfigLight();
	void ReflectionLight(D3DXVECTOR4);
	void SetUpLight();
	D3DXVECTOR3 GetPos(){
		return m_transform.position;
	}
private:
	CDirectInput* m_pInput;
	CLight m_light;
	D3DXVECTOR3 m_lightDir[NUM_DIFFUSE_LIGHT];
	D3DXVECTOR4 m_lightColor[NUM_DIFFUSE_LIGHT];
	short count;
	D3DXVECTOR3 dir;

	//ここからBulletPhysicsで衝突判定を行うためのメンバ変数。
	btGhostObject*		m_ghostObject;		//!<ゴースト。剛体の変わりになるもの。完全に物理挙動に任せたいものは剛体を使う。
	btSphereShape*		m_collisionShape;	//!<コリジョン形状。
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
	D3DXVECTOR3		m_position;
	float			m_radius;
	D3DXVECTOR3		m_moveSpeed;		//移動速度。
	float			g_currentAngleY;	//現在の方向
	float			g_targetAngleY;		//向きたい方向
	float			g_turnSpeed;		//回転速度
	bool			isTurn;				//回転フラグ
};

namespace tkEngine{
	const D3DXVECTOR3 vec3Zero = { 0.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3Right = { 1.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3Left = { -1.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3Up = { 0.0f, 1.0f, 0.0f };
	const D3DXVECTOR3 vec3Down = { 0.0f, -1.0f, 0.0f };
	const D3DXVECTOR3 vec3Front = { 0.0f, 0.0f, 1.0f };
	const D3DXVECTOR3 vec3Back = { 0.0f, 0.0f, -1.0f };

	const D3DXVECTOR3 vec3AxisX = { 1.0f, 0.0f, 0.0f };
	const D3DXVECTOR3 vec3AxisY = { 0.0f, 1.0f, 0.0f };
	const D3DXVECTOR3 vec3AxisZ = { 0.0f, 0.0f, 1.0f };
}