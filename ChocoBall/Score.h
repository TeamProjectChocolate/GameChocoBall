#pragma once
#include "Number.h"

#define TIMEBONUS 10
#define ENEMY_BONUS 20

class CScoreCalc
{
	int m_enemycounter = 0;
	int m_timecounter = 0;
	int m_totalscore = 0;
public:
	CScoreCalc();
	~CScoreCalc();
	void Draw();

	
	void SetEnemyCounter(int enemy)
	{
		m_enemycounter = enemy;
	}
	void SetTotalScore(int score)
	{
		m_totalscore = score;
	}
//public:
//
//
//	void SetViewMatrix(D3DXMATRIX view)
//	{
//		viewMatrix = view;
//	}
//	D3DXMATRIX GetViewMatrix()
//	{
//		return viewMatrix;
//	}
//
//
//
//
//	void SetProjectionMatrix(D3DXMATRIX pro)
//	{
//		projectionMatrix = pro;
//	}
//	D3DXMATRIX GatProjectionMatrix()
//	{
//		return projectionMatrix;
//	}
//
//	void InitProjectionMatrix();
//	void Update();
//
//
//
//
//	void SetVEyePt(D3DXVECTOR3 pt)
//	{
//		vEyePt = pt;
//	}
//
//	void SetLookatPt(D3DXVECTOR3 look)
//	{
//		vLookatPt = look;
//	}
//
//	void SetUpVec(D3DXVECTOR3 up)
//	{
//		vUpVec = up;
//	}
//};


//CCamera camera;
//	void CCamera::Update()
//	{
//		D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
//	}
//	void Update()
//	{
//		if (GetAsyncKeyState(VK_LEFT))
//		{
//			camera.SetVEyePt += 0.1f;
//		}
//		camera.Update();
//	}
};