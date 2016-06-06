#pragma once
#include "stdafx.h"


enum GimmickType{
	GimmickType_Chocoball,
	GimmickType_Wall,
};
struct SEnemyAndGimmickInfo{
	D3DXVECTOR3 pos;
	D3DXQUATERNION rot;
	D3DXVECTOR3 scale;
	int enemyType;
	int gimmickType;
};
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 scale;
};




// �X�e�[�W1�Ŏg�p����I�u�W�F�N�g�̒�`�z��
// ���V�����X�e�[�W��������瓯���������ŐV�����z���ǉ����Ă�������
// ���I�u�W�F�N�g�̖��O�́A�����X�e�[�W�̒��łȂ���Δ���Ă��\���܂���
static LPCSTR StageGameObject_1[] = {
	{ "BulletPhysics" },
	{ "TESTStage3D" },
	{ "2DTest" },
	{ "Number" },
	{ "Camera" },
	{ "EnemyManager" },
	{ "TEST3D" }
};

// ��ɐV�����z���ǉ������炱���ɂ��̃I�u�W�F�N�g�z��̃|�C���^�����Ԃǂ���Ɋi�[���Ă�������
// �����̌�A��ԉ��ɂ���A�z��̗v�f�����i�[����z����X�V���Ă�������

static LPCSTR* StageArray[] = {
	StageGameObject_1
};

// �X�e�[�W�I�u�W�F�N�g�z��̗v�f�����i�[����z��
static int StageObjectNumArray[] = {
	ARRAYSIZE(StageGameObject_1)
};



// �X�e�[�W1�Ŏg�p����M�~�b�N��G�l�~�[�̃|�W�V�����Ȃǂ�ݒ肵���z��
// ���X�e�[�W��ǉ������瓯���悤�Ȕz���V��������āA�ǉ������X�e�[�W�̏o�̓w�b�_�[��ǂݍ���ł�������
static SEnemyAndGimmickInfo infoTable_1[] = {
#include "EnemyGimmickInfo.h"
};

// �X�e�[�W1�Ŏg�p����M�~�b�N��G�l�~�[�̃|�W�V�����Ȃǂ�ݒ肵���z��̃|�C���^���i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static SEnemyAndGimmickInfo* infoTableArray[] = {
	infoTable_1
};

// �X�e�[�W1�Ŏg�p����M�~�b�N��G�l�~�[�̃|�W�V�����Ȃǂ�ݒ肵���z��̗v�f�����i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static int InfoTableSizeArray[] = {
	ARRAYSIZE(infoTable_1)
};



// �X�e�[�W1�Ŏg�p����M�~�b�N�����p�����蔻��
// ���X�e�[�W��ǉ������瓯���悤�Ȕz���V��������āA�ǉ������X�e�[�W�̏o�̓w�b�_�[��ǂݍ���ł�������
static SCollisionInfo GimmickTriggerInfoTable_1[] = {
#include "GimmickTriggerInfo.h"
};

// �X�e�[�W1�Ŏg�p����M�~�b�N�����p�����蔻���ݒ肵���z��̃|�C���^���i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static SCollisionInfo* GimmickinfoTableArray[] = {
	GimmickTriggerInfoTable_1
};

// �X�e�[�W1�Ŏg�p����M�~�b�N�����p�����蔻���ݒ肵���z��̗v�f�����i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static int GimmickInfoTableSizeArray[] = {
	ARRAYSIZE(GimmickTriggerInfoTable_1)
};



// �X�e�[�W1�̃t�B�[���h�̓����蔻��
// ���X�e�[�W��ǉ������瓯���悤�Ȕz���V��������āA�ǉ������X�e�[�W�̏o�̓w�b�_�[��ǂݍ���ł�������
static SCollisionInfo collisionInfoTable_1[] = {
#include "collisionInfo.h"
};

// �X�e�[�W1�̃t�B�[���h�̓����蔻���ݒ肵���z��̃|�C���^���i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static SCollisionInfo* collisionInfoTableArray[] = {
	collisionInfoTable_1
};

// �X�e�[�W1�ł̃t�B�[���h�̓����蔻���ݒ肵���z��̗v�f�����i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static int collisionInfoTableSizeArray[] = {
	ARRAYSIZE(collisionInfoTable_1)
};
