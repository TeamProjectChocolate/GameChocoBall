#include "stdafx.h"
#include "CourceCamera.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Infomation.h"
#include "CollisionType.h"


namespace{
	void VectorSmoothDamp(
		D3DXVECTOR3& vOut, 
		const D3DXVECTOR3& currentPos, 
		const D3DXVECTOR3& targetPos,
		D3DXVECTOR3& linearVelocity,
		int smoothTime
	)
	{
		D3DXVECTOR3 dist = targetPos - currentPos;
		D3DXVECTOR3 vel = dist /= smoothTime;
		linearVelocity = vel;
		vOut = currentPos + linearVelocity;
	}
}
void CCourceCamera::Initialize(){
	m_courceDef.SetStageID(m_StageID);
	m_courceDef.Initialize();
	CGameCamera::Initialize();
	m_CompCamera = false;
	m_isFirst = true;
	m_cameraPosSpeed.x = 0.0f;
	m_cameraPosSpeed.y = 0.0f;
	m_cameraPosSpeed.z = 0.0f;
	m_PrevCource = COURCE_BLOCK();
	m_PrevCource.blockNo = -1;
	m_CurrentCource.blockNo = 0;
	m_TurnFlg = false;
	m_IsEnd = false;
	m_IsTarget = true;
}

void CCourceCamera::Update(){

	if (m_GameState == GAMEEND_ID::CONTINUE){
		CPlayer* pl = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));
		D3DXVECTOR3 Target = pl->GetPos();
		m_CurrentCource = m_courceDef.FindCource(Target);
		m_PrevCource = m_courceDef.FindCource(m_CurrentCource.blockNo - 1);

		Target.y += 0.1f;
		if (m_IsTarget){
			m_camera.SetTarget(Target);
		}
		D3DXVECTOR3 courceVec = m_CurrentCource.endPosition - m_CurrentCource.startPosition;
		D3DXVECTOR3 Dir;
		D3DXVec3Normalize(&Dir, &courceVec);
		D3DXVECTOR3 TargetPos = pl->GetPos() - m_CurrentCource.startPosition;

		CourceTurn(Dir, TargetPos, D3DXToRadian(140.0f), 1.5f);

		TargetPos.y = Target.y + 2.5f;

		m_transform.position = m_NowPos;
		if (!m_isFirst){
			VectorSmoothDamp(
				m_NowPos,
				m_NowPos,
				TargetPos,
				m_cameraPosSpeed,
				10);
			m_Isintersect.IntersectCamera(&m_NowPos, &(m_NowPos - m_transform.position));
		}
		else{
			m_NowPos = TargetPos;
			m_transform.position = m_NowPos;
			m_Isintersect.CollisitionInitialize(&m_NowPos, 2.8f,CollisionType_Camera);
			m_isFirst = false;
		}
		m_camera.SetPos(m_NowPos);

		//m_camera.SetTarget(target);
	}
	else if (m_GameState == GAMEEND_ID::CLEAR){
		ClearCamera();
	}
	CGameCamera::Update();
}

void CCourceCamera::Draw(){
	CGameCamera::Draw();
}

void CCourceCamera::ClearCamera(){
	D3DXVECTOR3 courceVec = m_CurrentCource.startPosition - m_NowPos;
	float length = D3DXVec3Length(&courceVec);
	if (1.0f <= length){
		D3DXVECTOR3 Dir;
		D3DXVec3Normalize(&Dir, &courceVec);
		D3DXVECTOR3 TargetPos = m_CurrentCource.startPosition;
		TargetPos.y += 2.5f;
		VectorSmoothDamp(
			m_NowPos,
			m_NowPos,
			TargetPos,
			m_cameraPosSpeed,
			30);
		m_camera.SetPos(m_NowPos);
	}
	else{
		m_IsEnd = true;
	}
	if (m_IsEnd){
		return;
	}
	m_IsEnd = false;

}

void CCourceCamera::CourceTurn(D3DXVECTOR3& Dir, D3DXVECTOR3& Target, float kakudo, float length){
#if 0
	bool TurnFlg = false;
	// コースとコースの継ぎ目の角度が一定値以下の時はカメラが一定値以上離れないようにする
	D3DXVECTOR3 Vec1, Vec2;
	//if (m_CurrentCource.blockNo < m_OldCource.blockNo){
	//	//m_TurnFlg = false;
	//	return;
	//	Vec1 = m_CurrentCource.startPosition - m_CurrentCource.endPosition;
	//	Vec2 = m_OldCource.endPosition - m_OldCource.startPosition;
	//}
	//else{
	Vec1 = m_CurrentCource.endPosition - m_CurrentCource.startPosition;
	Vec2 = m_PrevCource.startPosition - m_PrevCource.endPosition;
	//}
	D3DXVec3Normalize(&Vec1, &Vec1);
	D3DXVec3Normalize(&Vec2, &Vec2);
	Vec1.y = 0.0f;
	Vec2.y = 0.0f;
	float cos = D3DXVec3Dot(&Vec1, &Vec2);
	float acos = acosf(cos);
	if (acos <= kakudo){
		TurnFlg = true;
	}

	float t = D3DXVec3Dot(&Dir, &Target);

	if (TurnFlg){
		if (t < 0.0f){
			Target = m_CurrentCource.startPosition + (Dir * (t - 4.0f));
		}
		else{
			Target = m_CurrentCource.startPosition + (Dir*(t - 8.0f));
		}
	}
	else{
		Target = m_CurrentCource.startPosition + (Dir*(t - 8.0f));
	}
	Target.y = 0.0f;
#else

	float t = D3DXVec3Dot(&Dir, &Target);
	if (fabsf(t) - 8.0f < 0.0f &&m_PrevCource.blockNo != -1){
		//プレイヤの座標を手前のコースに射影する。
		CPlayer* pl = SINSTANCE(CObjectManager)->FindGameObject<CPlayer>(_T("TEST3D"));
		D3DXVECTOR3 prevCourceDir = m_PrevCource.endPosition - m_PrevCource.startPosition;
		D3DXVec3Normalize(&prevCourceDir, &prevCourceDir);
		Target = pl->GetPos() - m_PrevCource.startPosition;
		t = D3DXVec3Dot(&prevCourceDir, &Target);
		Target = m_PrevCource.startPosition + (prevCourceDir*(t - 8.0f));
	}
	else{
		Target = m_CurrentCource.startPosition + (Dir*(t - 8.0f));
	}
	Target.y = 0.0f;
#endif
}