#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "DirectInput.h"
#include "Light.h"
#include "islntersect.h"
#include "Turn.h"
#include "GameManager.h"
#include "CourceDef.h"
#include "LockOn.h"

class LockOn;

class CPlayer : public C3DImage
{
public:
	CPlayer(){
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
	void Setradius(float radius)
	{
		m_radius = radius;
	}
	bool GetShotflag()
	{
		return m_Shotflag;
	}
	void SetShotflag(bool shotflag)
	{
		Shotflag=shotflag;
	}
private:
	CInterface*	m_pInput;
	CLight			m_light;
	D3DXVECTOR3		m_lightDir[NUM_DIFFUSE_LIGHT];
	D3DXVECTOR4		m_lightColor[NUM_DIFFUSE_LIGHT];	
	float			_X;
	D3DXVECTOR3		m_position;
	float			m_radius;
	D3DXVECTOR3		m_initPosition;		//初期座標。
	D3DXVECTOR3		m_moveSpeed;		//移動速度。
	float			m_currentAngleY;	//現在の方向
	float			m_targetAngleY;		//向きたい方向
	float			m_turnSpeed;		//回転速度
	bool			isTurn;				//回転フラグ
	bool            LockOnflag;			//ロックオンフラグ
	int				m_lockonEnemyIndex;	//ロックオンしている敵のインデックス。
	LockOn          m_LockOn;			//LockOnのインスタンス
	CIsIntersect	m_IsIntersect;		//CIsIntersectのインスタンス
	void UpdateLight();
	CTurn			m_Turn;				//CTurnのインスタンス
	bool			Shotflag;			//弾が発射されているのかのフラグ
	bool            Jumpflag;			//ジャンプフラグ
	bool			FrontBackflag, RightLeftflag;
	//bool			m_Shotflag;			//弾が発射されているのかのフラグ

	CCourceDef		m_Courcedef;
	//藤田
	D3DXVECTOR3		m_V1;
	D3DXVECTOR3		V1;
	D3DXVECTOR3		m_V2;
	D3DXVECTOR3		V2;
	D3DXVECTOR3		m_V3;
	float			V3;
	D3DXVECTOR3		m_Up;
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