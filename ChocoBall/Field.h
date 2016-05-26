#pragma once
#include "C3DImage.h"
#include "BulletPhysics.h"

#define MaxCollision 100

struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXQUATERNION rotation;
	D3DXVECTOR3 scale;
};

//コリジョンの種類
enum CollisionType{

};
class CField :
	public C3DImage
{
public:
	CField(){
		memset(m_ghostObject, 0, sizeof(m_ghostObject));//ghostobjectの配列を0からメモリ分初期化
		m_myMotionState = nullptr;
		m_myMotionState = nullptr;
		strcpy(m_pFileName, "image/SUTE2.x" /*"image/stage2.x"*/);
	};
	~CField();

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SetUpTechnique()override{
		m_pEffect->SetTechnique("ShadowTec");
	}
	
private:
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btGhostObject*		m_ghostObject[MaxCollision];		//!<ゴースト。剛体の変わりになるもの。完全に物理挙動に任せたいものは剛体を使う。
	btBoxShape*	m_groundShape[MaxCollision];	//地面のコリジョン形状。
	btBoxShape*	m_GhostShape[MaxCollision];	//当たり判定だけがあるコリジョン形状。
	btRigidBody*		m_rigidBody[MaxCollision];	//剛体。
	btDefaultMotionState* m_myMotionState;
	
};

