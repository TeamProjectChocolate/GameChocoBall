#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "DirectInput.h"
#include "Light.h"
#include "islntersect.h"

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
private:
	CDirectInput* m_pInput;
	CLight m_light;
	D3DXVECTOR3 m_lightDir[NUM_DIFFUSE_LIGHT];
	D3DXVECTOR4 m_lightColor[NUM_DIFFUSE_LIGHT];
	short count;
	D3DXVECTOR3 dir;

	D3DXVECTOR3		m_position;
	float			m_radius;
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x�B
	float			g_currentAngleY;	//���݂̕���
	float			g_targetAngleY;		//������������
	float			g_turnSpeed;		//��]���x
	bool			isTurn;				//��]�t���O
	CIsIntersect	m_IsIntersect;		//CIsIntersect�̃C���X�^���X

	void UpdateLight();
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