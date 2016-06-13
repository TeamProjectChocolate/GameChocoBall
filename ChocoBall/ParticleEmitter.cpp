#include "stdafx.h"
#include "ParticleEmitter.h"
#include "ObjectManager.h"
#include "RenderContext.h"


CParticleEmitter::CParticleEmitter()
{
	m_camera = nullptr;
	m_param = nullptr;
	m_timer = 0.0f;
	m_count = 0;
	strcpy(m_pFileName, "image/test.png");
}


CParticleEmitter::~CParticleEmitter()
{
}

void CParticleEmitter::Initialize(){
	m_count = 0;
	m_timer = 0.0f;
	m_random.Init(0.1);
	SetAlive(true);
}

void CParticleEmitter::Update(){
#if 0 //@todo デバッグのため
	if (m_timer >= m_param->intervalTime){
		//char num[10];
		//_itoa(m_count, num,10);
		//strcat(m_EmitterName, num);
		CParticle* p = SINSTANCE(CObjectManager)->GenerationObject<CParticle>(static_cast<LPCSTR>(m_EmitterName),PRIORTY::OBJECT2D_ALPHA,false);
		p->InitParticle(m_random, *m_camera, m_param, m_emitPosition);
		m_timer = 0.0f;
		m_ParticleList.push_back(p);
		m_count++;
	}
	m_timer += 1.0f / 60.0f;
	list<CParticle*>::iterator itr = m_ParticleList.begin();
	while (itr != m_ParticleList.end()){
		if ((*itr)->GetIsDead()){
			itr = m_ParticleList.erase(itr);
			m_count--;
		}
		else{
			itr++;
		}
	}
#endif
}

void CParticleEmitter::Draw(){

}

void CParticleEmitter::ApplyForce(const D3DXVECTOR3& applyForce){
	for (auto itr : m_ParticleList){
		itr->ApplyFource(applyForce);
	}
}
