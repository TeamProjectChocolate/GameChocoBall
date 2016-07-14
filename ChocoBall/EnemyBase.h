#pragma once 
#include "stdafx.h"
#include "C3DImage.h"
#include "StageTable.h"
#include "islntersect.h"

class CEnemyManager;

class EnemyBase : public C3DImage
{
public:
	virtual void OnDestroy();
	virtual void Update()override;
	void Build();
	void PlayerBulletHit(D3DXVECTOR3);
	void RollingEnemy();
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("NotNormalMapNonAnimationFresnelTec");
	}
	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
	bool GetIsHit(){
		return m_IsHit;
	}
protected:
	STAGE_ID m_StageID;
private:
	CIsIntersect m_IsIntersect;		//CIsIntersectのインスタンス
	float m_deadTimer;
	bool m_IsHit;
	CEnemyManager* m_pEnemyManager;
};