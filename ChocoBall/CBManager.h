#pragma once
#include "stdafx.h"
#include "C3DImage.h"
#include "ObjectManager.h"
#include "Chocoball.h"
#include "GameObject.h"
#include "Player.h"
#include "CourceDef.h"
#include "ShadowRender.h"


#define CHOCO_NUM 200	//���ɗ����`���R�̐�

struct SInstancingVertex{
	FLOAT x, y, z, w;
	DWORD color;
	FLOAT u, v;
	int Index;
public:
	void SetIndex(const int& index){
		this->Index = index;
	}
};
//Chocoball���Ǘ�����N���X
class CCBManager : public CGameObject{
public:
	CCBManager(){};
	~CCBManager(){
		for (int idx = 0; idx <= CHOCO_NUM; idx++){
			SINSTANCE(CShadowRender)->DeleteObjectImidieit(&m_Choco[idx]);
		}
	};
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void DrawDepth(LPD3DXEFFECT,const D3DXVECTOR2&)override;
	void FindCource();
	void NonActivate();

	//�i�s�������Z�b�g���܂��B
	void SetVector(D3DXVECTOR3 vec)
	{
		m_Vector = vec;
	}

	//�ŏ��̃|�W�V�������擾�ł��܂��B
	D3DXVECTOR3 GetStartPosition()
	{
		return m_pos;
	}


	//�ŏ��̃|�W�V�������Z�b�g���܂��B
	void SetStartPosition(D3DXVECTOR3 pos)
	{
		m_pos = pos;
	}

	//�I�_�̃|�W�V�������Z�b�g���܂��B
	void SetEndPosition(D3DXVECTOR3 Epos)
	{
		m_posG = Epos;
	}

	//�I�_�̃|�W�V�������擾�ł��܂��B
	D3DXVECTOR3 GetEndPosition()
	{
		return m_posG;
	}
	//�`���R�{�[���Ƃ̏Փ˔���B
	bool IsHit(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	
	void SetStageID(STAGE_ID id){
		m_StageID = id;
	}
	int GetCourceNo(){
		return m_InitPosOfCourceNo;
	}
private:
	D3DXVECTOR3			m_pos;			//���������ꏊ�̃|�W�V�����B
	D3DXVECTOR3			m_posG;			//����Ă�����(�S�[��)�̃|�W�V�����B
	D3DXVECTOR3			m_Vector;		//�`���R�̐i�s�����B
	CChocoBall			m_Choco[CHOCO_NUM];
	float				m_interval;		//�C���^�[�o���B
	float				m_timer;		//�^�C�}�[�B
	int					m_numCreate;	//�쐬�ς݂̃`���R�{�[���̐��B
	int					m_InitPosOfCourceNo;// �`���R�{�[�����������ꂽ�ꏊ�̃R�[�X�i���o�[
	CCourceDef m_CourceDef;
	STAGE_ID m_StageID;
	bool m_IsFirst;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
};