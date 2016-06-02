#pragma once
#include "GameObject.h"
#include "CourceCamera.h"
#include "Particle.h"

#define MAX_NAME 256

// パーティクル生成パラメータ
typedef struct SParticleEmitParameter{
	void Init(){
		memset(this, 0, sizeof(SParticleEmitParameter));
		initAlpha = 0.0f;
		uvTableSize = 1;
		brightness = 1.0f;
		isBillboard = true;
	};
	const char* texturePath;	// テクスチャのファイルパス
	D3DXVECTOR3 initVelocity;	// 初速度
	float life;					// 寿命
	float intervalTime;			// 発生時間
	float w;					// パーティクルの幅
	float h;					// パーティクルの高さ
	D3DXVECTOR3 initPositionRandomMargin;	// 初期位置のランダム幅
	D3DXVECTOR3 initVelocityVelocityRandomMargin;	// 初速度のランダム幅
	D3DXVECTOR3 addVelocityRandomMargin;			// 速度の積分のときのランダム幅
	D3DXVECTOR4 uvTable[4];		// uvテーブル。最大4まで保存できる。xが左上のu。yが左上のv。zが右下のu。wが右下のvになる。
	int uvTableSize;			// uvテーブルのサイズ
	D3DXVECTOR3 gravity;		// 重力
	bool isFade;				// 死ぬときにフェードアウトするか
	float fadeTime;				// フェードする時間
	float initAlpha;			// 初期アルファ値
	bool isBillboard;			// ビルボード？
	float brightness;			// 輝度。ブルームが有効になっているとこれを強くすると光があふれる
	int alphaBlendMode;			// 半透明合成、1加算合成
};

// パーティクルの発生機
class CParticleEmitter:public CGameObject
{
public:
	CParticleEmitter();
	~CParticleEmitter();
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void ApplyForce(const D3DXVECTOR3&);
	void SetCamera(CCamera* camera){
		m_camera = camera;
	}
	void SetEmitParameter(SParticleEmitParameter* param){
		m_param = param;
	}
	void SetEmitPos(D3DXVECTOR3 pos){
		m_emitPosition = pos;
	}
	void SetEmitterName(LPCSTR name){
		CH_ASSERT(strlen(name) < MAX_NAME);
		strcpy(m_EmitterName, name);
	}
private:
	float m_timer;
	CRandom m_random;
	CCamera* m_camera;
	SParticleEmitParameter* m_param;
	D3DXVECTOR3 m_emitPosition;
	list<CParticle*> m_ParticleList;
	list<CParticle*> m_deleteParticleList;
	char m_EmitterName[MAX_NAME];
	int m_count;
};

