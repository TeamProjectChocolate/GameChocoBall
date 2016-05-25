#include "stdafx.h"
#include "Animation.h"
#include "Assert.h"


CAnimation::~CAnimation()
{
}

void CAnimation::Initialize(ID3DXAnimationController* anim){
	m_pAnimController = anim;
	ID3DXAnimationSet* animSet;
	m_pAnimController->GetAnimationSet(0, &animSet);
	m_numAnimSet = m_pAnimController->GetMaxNumAnimationSets();
	m_numMaxTracks = m_pAnimController->GetMaxNumTracks();
	m_blendRateTable.reset(new float[m_numMaxTracks]);
	m_AnimationSets.reset(new ID3DXAnimationSet*[m_numAnimSet]);
	for (int i = 0; i < m_numMaxTracks; i++){
		m_blendRateTable[i] = 1.0f;
	}
	// �A�j���[�V�����Z�b�g��������
	for (int i = 0; i < m_numAnimSet; i++){
		m_pAnimController->GetAnimationSet(i, &m_AnimationSets[i]);
	}
}

#if 0
void CAnimation::BlendAnimation(int animationSetIndex){
	if(m_pAnimController){
		isBlending = true;
		currentTrackNo++;
		currentTrackNo %= numAnimSet;
		m_pAnimController->SetTrackWeight(0,0.0f);
		m_pAnimController->SetTrackWeight(1,1.0f);
		m_pAnimController->SetTrackSpeed(0,1.0f);
		m_pAnimController->SetTrackSpeed(1,1.0f);
		m_pAnimController->SetTrackEnable(currentTrackNo,m_AnimationSets[animationSetIndex]);
	}
}
#endif

void CAnimation::PlayAnimation(int animationSetIndex){
	if (animationSetIndex < m_numAnimSet){
		if (m_pAnimController){
			m_oldAnimationSetNo = m_currentAnimationSetNo;
			m_currentAnimationSetNo = animationSetIndex;
			if (m_oldAnimationSetNo == m_currentAnimationSetNo){
				return;
			}
			m_currentTrackNo = 0;
			// 0�ԖڈȊO�̃g���b�N�͖����ɂ���
			for (int i = 0; i < m_numMaxTracks; i++){
				m_pAnimController->SetTrackEnable(i, false);
			}
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackAnimationSet(m_currentTrackNo, m_AnimationSets[m_currentAnimationSetNo]);
			m_pAnimController->SetTrackEnable(0, true);
			m_pAnimController->SetTrackPosition(0, 0.0f);
		}
	}
	else{
		Assert(animationSetIndex < m_numAnimSet);
	}
}

void CAnimation::PlayAnimation(int animationSetIndex, float interpolateTime){
	if (animationSetIndex < m_numAnimSet){
		if (m_pAnimController){
			m_oldAnimationSetNo = m_currentAnimationSetNo;
			m_currentAnimationSetNo = animationSetIndex;
			if (m_oldAnimationSetNo == m_currentAnimationSetNo){
				return;
			}

			// ��Ԓ��t���O��true�ɂ���
			m_isInterpolate = true;
			this->m_interpolateTime = 0.0f;
			m_interpolateEndTime = interpolateTime;
			m_currentTrackNo = (m_currentTrackNo + 1) % m_numMaxTracks;
			m_pAnimController->SetTrackAnimationSet(m_currentTrackNo, m_AnimationSets[m_currentAnimationSetNo]);
			m_pAnimController->SetTrackEnable(m_currentTrackNo, true);
			m_pAnimController->SetTrackSpeed(m_currentTrackNo, 1.0f);
			m_pAnimController->SetTrackPosition(m_currentTrackNo, 0.0f);
		}
	}
}

void CAnimation::Update(float deltaTime){
	if (m_pAnimController){
		m_pAnimController->AdvanceTime(deltaTime, nullptr);
		if (m_isInterpolate){
			// ��Ԓ�
			m_interpolateTime += deltaTime;
			float weight = 0.0f;
			if (m_interpolateTime > m_interpolateEndTime){
				// ��ԏI��
				m_isInterpolate = false;
				weight = 1.0f;
				// ���݂̃g���b�N�ȊO�𖳌��ɂ���
				for (int i = 0; i < m_numMaxTracks; i++){
					if (i != m_currentTrackNo){
						m_pAnimController->SetTrackEnable(i, false);
					}
				}
			}
			else{
				weight = m_interpolateTime / m_interpolateEndTime;
				float invWeight = 1.0f - weight;
				// �E�F�C�g��ݒ肵�Ă���
				for (int i = 0; i < m_numMaxTracks; i++){
					if (i != m_currentTrackNo){
						m_pAnimController->SetTrackWeight(i, m_blendRateTable[i] * invWeight);
					}
					else{
						m_pAnimController->SetTrackWeight(i, weight);
					}
				}
			}
		}
	}
}
