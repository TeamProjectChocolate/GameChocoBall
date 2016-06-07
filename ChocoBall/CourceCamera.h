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
	COURCE_BLOCK m_OldCource;	// �v���C���[�������t���[���O�ɂ����u���b�N
	COURCE_BLOCK m_NowCource;	// �v���C���[�����݂���u���b�N
	bool m_CompCamera;			// �J�����̕⊮����	
	D3DXVECTOR3 m_NowPos;		// ���݂̃J�����̈ʒu
	D3DXVECTOR3 m_cameraPosSpeed;	//�J�����̈ړ����x�B
	bool m_isFirst;
	STAGE_ID m_StageID;
};

