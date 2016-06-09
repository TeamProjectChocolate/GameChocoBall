#pragma once
#include "stdafx.h"


enum GimmickType{
	GimmickType_Chocoball,
	GimmickType_Wall,
	GimmickType_FallFloor,
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



// �t�B�[���h��X�t�@�C����
// ���ォ�珇�ɃX�e�[�W1,2,3�c�c
static LPCSTR FieldNameArray[] = {
	"image/SUTE2_01.x",
	"image/SUTE2_01.x"
};


// �X�e�[�W1�Ŏg�p����I�u�W�F�N�g�̒�`�z��
// ���V�����X�e�[�W��������瓯���������ŐV�����z���ǉ����Ă�������
// ���I�u�W�F�N�g�̖��O�́A�����X�e�[�W�̒��łȂ���Δ���Ă��\���܂���
// �����̔z��ɐV�������O�̃I�u�W�F�N�g��ǉ�������Stage.cpp��ActivateObjects�֐���if����ǉ����Ă�������
static LPCSTR StageGameObject_1[] = {
	{ "BulletPhysics" },// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
	{ "TESTStage3D" },// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
	{ "Number" },// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
	{ "Camera" },// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
	{ "EnemyManager" },// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
	{ "TEST3D" },// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
	{ "2DTest" },
};
static LPCSTR StageGameObject_2[] = {
	{ "BulletPhysics" },	// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
	{ "TESTStage3D" },	// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
	{ "Number" },	// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
	{ "Camera" },	// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
	{ "EnemyManager" },	// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
	{ "TEST3D" },	// ���ׂẴX�e�[�W�ɂ��ꂪ�K�v�ł�
};

// ��ɐV�����z���ǉ������炱���ɂ��̃I�u�W�F�N�g�z��̃|�C���^�����Ԃǂ���Ɋi�[���Ă�������
// �����̌�A��ԉ��ɂ���A�z��̗v�f�����i�[����z����X�V���Ă�������

static LPCSTR* StageArray[] = {
	StageGameObject_1,
	StageGameObject_2
};

// �X�e�[�W�I�u�W�F�N�g�z��̗v�f�����i�[����z��
static int StageObjectNumArray[] = {
	ARRAYSIZE(StageGameObject_1),
	ARRAYSIZE(StageGameObject_2)
};



// �X�e�[�W���Ƃ̃v���C���[�̃|�W�V���������i�[
static SCollisionInfo PlayerTransformArray[] = {
#include "PlayerPositionInfoStage1.h"
#include "PlayerPositionInfoStage2.h"
};



// �X�e�[�W1�Ŏg�p����M�~�b�N��G�l�~�[�̃|�W�V�����Ȃǂ�ݒ肵���z��
// ���X�e�[�W��ǉ������瓯���悤�Ȕz���V��������āA�ǉ������X�e�[�W�̏o�̓w�b�_�[��ǂݍ���ł�������
static SEnemyAndGimmickInfo infoTable_1[] = {
#include "EnemyGimmickInfoStage1.h"
};
static SEnemyAndGimmickInfo infoTable_2[] = {
#include "EnemyGimmickInfoStage2.h"
};

// �X�e�[�W1�Ŏg�p����M�~�b�N��G�l�~�[�̃|�W�V�����Ȃǂ�ݒ肵���z��̃|�C���^���i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static SEnemyAndGimmickInfo* infoTableArray[] = {
	infoTable_1,
	infoTable_2
};

// �X�e�[�W1�Ŏg�p����M�~�b�N��G�l�~�[�̃|�W�V�����Ȃǂ�ݒ肵���z��̗v�f�����i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static int InfoTableSizeArray[] = {
	ARRAYSIZE(infoTable_1),
	ARRAYSIZE(infoTable_2)
};



// �X�e�[�W1�Ŏg�p����M�~�b�N�����p�����蔻��
// ���X�e�[�W��ǉ������瓯���悤�Ȕz���V��������āA�ǉ������X�e�[�W�̏o�̓w�b�_�[��ǂݍ���ł�������
static SCollisionInfo GimmickTriggerInfoTable_1[] = {
#include "GimmickTriggerInfoStage1.h"
};
static SCollisionInfo GimmickTriggerInfoTable_2[] = {
#include "GimmickTriggerInfoStage2.h"
};

// �X�e�[�W1�Ŏg�p����M�~�b�N�����p�����蔻���ݒ肵���z��̃|�C���^���i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static SCollisionInfo* GimmickinfoTableArray[] = {
	GimmickTriggerInfoTable_1,
	GimmickTriggerInfoTable_2
};

// �X�e�[�W1�Ŏg�p����M�~�b�N�����p�����蔻���ݒ肵���z��̗v�f�����i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static int GimmickInfoTableSizeArray[] = {
	ARRAYSIZE(GimmickTriggerInfoTable_1),
	ARRAYSIZE(GimmickTriggerInfoTable_2)
};



// �X�e�[�W1�̃t�B�[���h�̓����蔻��
// ���X�e�[�W��ǉ������瓯���悤�Ȕz���V��������āA�ǉ������X�e�[�W�̏o�̓w�b�_�[��ǂݍ���ł�������
static SCollisionInfo collisionInfoTable_1[] = {
#include "collisionInfoStage1.h"
};
static SCollisionInfo collisionInfoTable_2[] = {
#include "collisionInfoStage2.h"
};


// �X�e�[�W1�̃t�B�[���h�̓����蔻���ݒ肵���z��̃|�C���^���i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static SCollisionInfo* collisionInfoTableArray[] = {
	collisionInfoTable_1,
	collisionInfoTable_2
};

// �X�e�[�W1�ł̃t�B�[���h�̓����蔻���ݒ肵���z��̗v�f�����i�[����z��
// ���X�e�[�W��ǉ������牺�̂悤�ȏ������Ŕz��ɗv�f��ǉ����Ă�������
static int collisionInfoTableSizeArray[] = {
	ARRAYSIZE(collisionInfoTable_1),
	ARRAYSIZE(collisionInfoTable_2)
};
