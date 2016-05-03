#pragma once
#include "stdafx.h"
#include "BulletPhysics.h"
#include "C3DImage.h"


class CDebri : public C3DImage {
public:
	void Initialize();
	void Update();
	void Draw();
	void OnDestroy();
	/*!
	*@brief	�\�z�����B
	*@param[in]	size	���̃T�C�Y�B
	*@param[in]	pos		���̍��W�B
	*/
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
private:
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_collisionShape;	//�R���W�����̌`��B
	btRigidBody*		m_rigidBody;		//���́B
	btDefaultMotionState* m_myMotionState;
	float m_life;
};