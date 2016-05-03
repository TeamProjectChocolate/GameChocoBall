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
	*@brief	構築処理。
	*@param[in]	size	箱のサイズ。
	*@param[in]	pos		箱の座標。
	*/
	void Build(const D3DXVECTOR3& size, const D3DXVECTOR3& pos);
private:
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_collisionShape;	//コリジョンの形状。
	btRigidBody*		m_rigidBody;		//剛体。
	btDefaultMotionState* m_myMotionState;
	float m_life;
};