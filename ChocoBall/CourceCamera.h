#pragma once
#include "GameCamera.h"
#include "CourceDef.h"
#include "islntersect.h"

class CCourceCamera :
	public CGameCamera
{
public:
	CCourceCamera(){};
	~CCourceCamera(){};
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void CourceTurn(D3DXVECTOR3&,D3DXVECTOR3&,float,float);
	void ClearCamera();
	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
	void SetGameState(GAMEEND_ID id){
		m_GameState = id;
	}
	bool GetIsEnd(){
		return m_IsEnd;
	}
	void SetIsTarget(bool flg){
		m_IsTarget = flg;
	}
private:
	CCourceDef m_courceDef;
	COURCE_BLOCK m_PrevCource;	// �v���C���[�������t���[���O�ɂ����u���b�N
	COURCE_BLOCK m_CurrentCource;	// �v���C���[�����݂���u���b�N
	bool m_CompCamera;			// �J�����̕⊮����	
	D3DXVECTOR3 m_NowPos;		// ���݂̃J�����̈ʒu
	D3DXVECTOR3 m_cameraPosSpeed;	//�J�����̈ړ����x�B
	bool m_isFirst;
	STAGE_ID m_StageID;
	bool m_TurnFlg;
	GAMEEND_ID m_GameState;
	bool m_IsEnd;
	CIsIntersect m_Isintersect;
	bool m_IsTarget;
	D3DXVECTOR3 m_Dir;
	D3DXVECTOR3 m_TargetPos;
};

