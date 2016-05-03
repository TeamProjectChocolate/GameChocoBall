#pragma once
#include "C3DImage.h"
#include "BulletPhysics.h"

class CField :
	public C3DImage
{
public:
	CField();
	~CField();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("ShadowTec");
	}
private:
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btGhostObject*		m_ghostObject;		//!<ゴースト。剛体の変わりになるもの。完全に物理挙動に任せたいものは剛体を使う。
	btCollisionShape*	m_groundShape;	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody;	//剛体。
	btDefaultMotionState* m_myMotionState;
};

