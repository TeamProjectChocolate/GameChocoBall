#include "stdafx.h"
#include "Particle.h"
#include "ObjectManager.h"
#include "ParticleEmitter.h"


CParticle::CParticle()
{
	strcpy(m_pFileName, "image/test.png");
	m_applyFource = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

CParticle::~CParticle()
{
	m_Primitive.Release();
}

void CParticle::Initialize(){
	C2DImage::Initialize();
}

void CParticle::Update(){
	m_timer += m_deltaTime;
	D3DXVECTOR3 addGravity = m_ParticleData.gravity;
	addGravity *= m_deltaTime;
	m_ParticleData.velocity += addGravity;
	D3DXVECTOR3 force = m_applyFource;
	force.x += (static_cast<float>(m_random->GetRandDouble() - 0.5f) * 2.0f) * m_addVelocityRandomMargin.x;
	force.y += (static_cast<float>(m_random->GetRandDouble() - 0.5f) * 2.0f) * m_addVelocityRandomMargin.y;
	force.z += (static_cast<float>(m_random->GetRandDouble() - 0.5f) * 2.0f) * m_addVelocityRandomMargin.z;
	force *= m_deltaTime;
	D3DXVECTOR3 addPos = m_ParticleData.velocity;
	addPos *= m_deltaTime;
	m_applyFource = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_ParticleData.position += addPos;

}

void CParticle::Draw(){
	SetupMatrices();
	SetUpTechnique();
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	(*graphicsDevice()).SetRenderState(D3DRS_ZENABLE, true
		
		/*false*/);
	(*graphicsDevice()).SetRenderState(D3DRS_ZWRITEENABLE, false);

	switch (m_alphaBlendMode){
	case 0:
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	case 1:
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);



		(*graphicsDevice()).SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);




		break;
	}
	m_pEffect->BeginPass(0);	//パスの番号を指定してどのパスを使用するか指定


	//SINSTANCE(CRenderContext)->GetCurrentCamera()->SetCamera(m_pEffect);
	//ここで固定描画と同じように、ローカル座標に設定された頂点群をデバイスに渡す。通常と同じ方法。
	//	メッシュも同じく、マテリアルやテクスチャを設定
	//DrawSubset()を呼び出して描画

	(*graphicsDevice()).SetStreamSource(0, m_Primitive.GetVertexBuffer(), 0, sizeof(SShapeVertex_PT));
	(*graphicsDevice()).SetIndices(m_Primitive.GetIndexBuffer());
	(*graphicsDevice()).SetVertexDeclaration(m_Primitive.GetVertexDecl());

	m_pEffect->SetMatrix("World", &mWorld);
	m_pEffect->SetInt("Split_X", m_Split.x);
	m_pEffect->SetInt("Split_Y", m_Split.y);
	m_pEffect->SetInt("NowCol", m_Now.x);
	m_pEffect->SetInt("NowRow", m_Now.y);

	float ratio_X = m_pImage->RealSize.x / m_pImage->UnRealSize.x;
	float ratio_Y = m_pImage->RealSize.y / m_pImage->UnRealSize.y;

	m_pEffect->SetFloat("Ratio_X", ratio_X);
	m_pEffect->SetFloat("Ratio_Y", ratio_Y);

	m_pEffect->SetTexture("g_Texture", m_pImage->pTex /*テクスチャ情報*/);
	m_pEffect->SetFloat("g_brightness", m_brightness);
	m_pEffect->SetFloat("Alpha", GetAlpha());
	m_pEffect->CommitChanges();				//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。

	(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	m_pEffect->EndPass();
	m_pEffect->End();



	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	(*graphicsDevice()).SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, false);



	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	(*graphicsDevice()).SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void CParticle::SetupMatrices(){
	D3DXMATRIX Trans;
	D3DXMatrixIdentity(&mWorld);
	D3DXMATRIX Scale;
	D3DXMatrixIdentity(&Scale);
	D3DXMatrixScaling(&Scale, m_transform.scale.x, m_transform.scale.y, m_transform.scale.z);
	D3DXMatrixMultiply(&mWorld, &mWorld, &Scale);

	D3DXMatrixIdentity(&Trans);
	D3DXMatrixTranslation(&Trans, m_ParticleData.position.x, m_ParticleData.position.y, m_ParticleData.position.z);
	if (m_isBillboard){
		// ビルボード処理
		const D3DXMATRIX CameraRota = m_camera->GetCameraRotation();
		D3DXMatrixMultiply(&mWorld, &mWorld, &CameraRota);
	}
	else{
		D3DXMatrixMultiply(&mWorld,&mWorld,&Trans);
	}

	D3DXMatrixMultiply(&mWorld, &mWorld, &Trans);

	switch (m_state){
	case EMIT_STATE::RUN:
		if (m_timer >= m_life){
			if (m_isFade){
				m_state = EMIT_STATE::FADEOUT;
				m_timer = 0.0f;
			}
			else{
				m_state = EMIT_STATE::DEAD;
			}
		}
		break;
	case EMIT_STATE::FADEOUT:{
		float t = m_timer / m_fadeTime;
		m_timer += m_deltaTime;
		SetAlpha(m_initAlpha + (-m_initAlpha)*t);
		if (GetAlpha() <= 0.0f){
			SetAlpha(0.0f);
			m_state = EMIT_STATE::DEAD;
		}
	}break;
	case EMIT_STATE::DEAD:
		SINSTANCE(CObjectManager)->DeleteGameObject(this);
		break;
	}
	D3DXMatrixMultiply(&mWorld, &mWorld, &(m_camera->GetView()));
	D3DXMatrixMultiply(&mWorld, &mWorld, &(m_camera->GetProj()));
}

void CParticle::InitParticle(CRandom& random, CCamera& camera, const SParticleEmitParameter* param, const D3DXVECTOR3& emitPosition,D3DXVECTOR3 dir){
	m_pEffect = SINSTANCE(CEffect)->SetEffect(_T("Shader/2DShader.hlsl"));	// 使用するshaderファイルを指定(デフォルト)

	if (param->size_randMax < param->size_randMin){
		MessageBox(nullptr, _T("MaxとMinの数字が逆転しています"), _T("警告"), MB_OK);
		abort();
	}
	float rand = (static_cast<float>(random.GetRandDouble()) * (param->size_randMax - param->size_randMin)) + param->size_randMin;

	float width = param->w * rand;
	float hight = param->h * rand;

	m_transform.scale = D3DXVECTOR3(width, hight, 1.0f);

	float halfW = param->w * 0.5f;
	float halfH = param->h * 0.5f;
	CH_ASSERT(param->uvTableSize <= ARRAYSIZE(param->uvTable));
	D3DXVECTOR4 uv;
	if (param->uvTableSize > 0){
		uv = param->uvTable[random.GetRandInt() % param->uvTableSize];
	}
	else{
		uv = param->uvTable[0];
	}

	SShapeVertex_PT vp[] = {
		{ -halfW, halfH, 0.0f, 1.0f, uv.x, uv.y },
		{ halfW, halfH, 0.0f, 1.0f, uv.z, uv.y },
		{ -halfW, -halfH, 0.0f, 1.0f, uv.x, uv.w },
		{ halfW, -halfH, 0.0f, 1.0f, uv.z, uv.w }
	};
	short index[]{
		0, 1, 2, 3
	};
	m_Primitive.Create(
		EType::eTriangleStrip,
		4,
		sizeof(SShapeVertex_PT),
		scShapeVertex_PT_Element,
		vp,
		4,
		D3DFMT_INDEX16,
		index);

	CH_ASSERT(strlen(param->texturePath) <= MAX_FILENAME);
	strcpy(m_pFileName, param->texturePath);
	C2DImage::SetImage();
	m_camera = &camera;
	m_random = &random;
	m_life = param->life;

	m_ParticleData.velocity = dir * D3DXVec3Length(&(param->initVelocity));

	m_ParticleData.velocity.x += ((static_cast<float>(random.GetRandDouble()) - 0.5f) * 2.0f) * param->initVelocityVelocityRandomMargin.x;
	m_ParticleData.velocity.y += ((static_cast<float>(random.GetRandDouble()) - 0.5f) * 2.0f) * param->initVelocityVelocityRandomMargin.y;
	m_ParticleData.velocity.z += ((static_cast<float>(random.GetRandDouble()) - 0.5f) * 2.0f) * param->initVelocityVelocityRandomMargin.z;
	m_ParticleData.position = emitPosition;
	m_ParticleData.position.x += ((static_cast<float>(random.GetRandDouble()) - 0.5f) * 2.0f) * param->initPositionRandomMargin.x;
	m_ParticleData.position.y += ((static_cast<float>(random.GetRandDouble()) - 0.5f) * 2.0f) * param->initPositionRandomMargin.y;
	m_ParticleData.position.z += ((static_cast<float>(random.GetRandDouble()) - 0.5f) * 2.0f) * param->initPositionRandomMargin.z;
	m_addVelocityRandomMargin = param->addVelocityRandomMargin;
	m_ParticleData.gravity = param->gravity;
	m_isFade = param->isFade;
	m_state = EMIT_STATE::RUN;
	m_initAlpha = param->initAlpha;
	SetAlpha(m_initAlpha);
	m_fadeTime = param->fadeTime;
	m_isBillboard = param->isBillboard;
	m_brightness = param->brightness;
	m_alphaBlendMode = param->alphaBlendMode;
	m_rotateZ = fPI * 2.0f * static_cast<float>(random.GetRandDouble());
	m_deltaTime = 1.0f / 60.0f;
	
	SetAlive(true);
}