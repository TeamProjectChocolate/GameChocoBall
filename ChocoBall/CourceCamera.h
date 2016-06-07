#pragma once
#include "GameCamera.h"
#include "CourceDef.h"

class CCourceCamera :
	public CGameCamera
{
public:
	CCourceCamera(){};
	~CCourceCamera(){};
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
private:
	CCourceDef m_courceDef;
	COURCE_BLOCK m_OldCource;	// プレイヤーがワンフレーム前にいたブロック
	COURCE_BLOCK m_NowCource;	// プレイヤーが現在いるブロック
	bool m_CompCamera;			// カメラの補完処理	
	D3DXVECTOR3 m_NowPos;		// 現在のカメラの位置
	D3DXVECTOR3 m_cameraPosSpeed;	//カメラの移動速度。
	bool m_isFirst;
	STAGE_ID m_StageID;
};

