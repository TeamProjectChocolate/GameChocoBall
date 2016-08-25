#pragma once
#include "Infomation.h"
#include "Effect.h"
#include "Assert.h"


class CGameObject
{
public:
	CGameObject(){
		m_pEffect = nullptr;
		m_OriginalInit = false;
		m_ManagerNewFlg = false;
		m_alpha = 1.0f;
		m_alive = false;
	};
	virtual ~CGameObject();
	virtual void OnDestroy(){};		// ObjectManager�N���X��DeleteGameObject�֐����Ă΂ꂽ�Ƃ��ɌĂяo�����֐�
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void DrawDepth(LPD3DXEFFECT,const D3DXVECTOR2&);
	virtual void SetUpTechnique();	// �G�t�F�N�g�̃e�N�j�b�N��ς���ꍇ�͌p����ł��̊֐���override���Ă�������
	void SetFileName(LPCSTR Name){
		CH_ASSERT(strlen(Name) < MAX_FILENAME);
		strcpy(m_pFileName, Name);
	}
	void SetAlive(bool alive){
		m_alive = alive;
	}
	bool GetAlive(){
		return m_alive;
	}
	bool GetOriginal(){
		return m_OriginalInit;
	}
	void ActiveManagerNewFlg(){
		m_ManagerNewFlg = true;
	}
	bool GetManagerNewFlg(){
		return m_ManagerNewFlg;
	}
	virtual void SetPos(D3DXVECTOR3 pos){
		m_transform.position = pos;
	}
	virtual D3DXVECTOR3 GetPos()
	{
		return m_transform.position;
	}
	virtual void SetScale(const D3DXVECTOR3 scale){
		m_transform.scale = scale;
	}
	D3DXVECTOR3 GetmoveSpeed()
	{
		return m_moveSpeed;

	}
	void SetAlpha(float alpha){
		m_alpha = alpha;
	}
	float GetAlpha(){
		return m_alpha;
	}
	void SetCommon(bool common){
		m_common = common;
	}
	bool GetCommon(){
		return m_common;
	}
protected:
	CHAR m_pFileName[MAX_FILENAME + 1];		// �ǂݍ��ރt�@�C���̖��O���i�[����
	TRANSEFORM m_transform; // �I�u�W�F�N�g�̍��W�A��]�A�傫�����
	D3DXVECTOR3 m_moveSpeed;
// �I�[�o�[���[�h�������t���O
// (�p����̃N���X��Initialize�֐��̃I�[�o�[���[�h���g�p�����ꍇ�́A���̃t���O�����̃N���X���ŕK��true�ɂ��Ă�������)
	bool m_OriginalInit;
	LPD3DXEFFECT m_pEffect;		// �g�p����G�t�F�N�g
private:
	bool m_ManagerNewFlg;	// ObjectManager�N���X��new���ꂽ���̂����肷��ϐ�
	bool m_alive;			// �����t���O(true�Ȃ琶���Afalse�Ȃ玀�S)
	float m_alpha;			// �I�u�W�F�N�g�̓����x(�f�t�H���g��1�A�����x���w�肵�����ꍇ�͌p����ŔC�ӂ̒l��ݒ肵�Ă�������)
	bool m_common;			// �풓�t���O(true�Ȃ�V�[���؂�ւ��ō폜����Ȃ�)
};

