#pragma once

enum CollisionType{
	CollisionType_Player,			//�v���C���[�̃R���W�����B
	CollisionType_Map,				//�n�`�R���W�����B
	CollisionType_Chocoball,		//�`���R�{�[���B
	CollisionType_ChocoballTrigger,	//�`���R�{�[���N���R���W�����B
	CollisionType_Camera,			//�J�����̃R���W����
	CollisionType_Wall,				//�`���R�ǂ̃R���W����
	CollisionType_Bullet,				//�e�̃R���W����
	CollisionType_Enemy
};