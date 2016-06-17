#pragma once
#include "xact3.h"

typedef struct AUDIO_SET{
	IXACT3Engine* pEngine;	//XACT�G���W��
	IXACT3WaveBank* pWaveBank;  //�E�F�[�u�o���N
	IXACT3SoundBank* pSoundBank;	//�T�E���h�o���N
	const char* xactEngineName;	//XACT�G���W����
	const char* waveBankName;   //�E�F�[�u�o���N��
	const char* soundBankName;	//�T�E���h�o���N��
	VOID* pbWaveBank;           //�E�F�[�u�o���N�n���h��
	VOID* pbSoundBank; // �T�E���h�o���N�n���h��
	XACTINDEX cueIndex;                //�L���[�C���f�b�N�X

}AOUDI_SET;

//XACT������
class CAudio{
public:
	CAudio();
	~CAudio();
	//XACT�������֐��i�G���W�����A�E�F�[�u�o���N���A�T�E���h�o���N��)
	HRESULT Initialize(const char*, const char*, const char*);
	//�G���W���쐬
	HRESULT CreateEngine(const char*);
	//�E�F�[�u�o���N�쐬
	HRESULT CreateWaveBank(const char*);
	//�T�E���h�o���N�쐬
	HRESULT CreateSoundBank(const char*);
	//XACT�G���W���̎����I�^�X�N���s�p
	void Run();
	//XACT�I���֐�
	void CleanupXACT();

	//�L���[�Đ��֐�(�L���[��)
	//������:const char*�^ �T�E���h��
	//		 bool�^ �����d�˂čĐ����邩�̃t���O(true�Ȃ�d�˂�,false�Ȃ�d�˂Ȃ�)
	void PlayCue(const char*,bool);

	//�L���[��~�֐�(�L���[��)
	void StopCue(const char*);

	void AddSoundName(LPCSTR name){
		char* work = new char[FILENAME_MAX];
		strcpy(work, name);
		m_SoundNameArray.push_back(work);
	}

	void DeleteName(LPCSTR name){
		for (vector<LPCSTR>::iterator itr = m_SoundNameArray.begin(); itr != m_SoundNameArray.end();){
			if (!strcmp(name, *itr)){
				SAFE_DELETE(*itr);
				itr = m_SoundNameArray.erase(itr);
				return;
			}
			else{
				itr++;
			}
		}
	}

	void DeleteNameAll(){
		for (vector<LPCSTR>::iterator itr = m_SoundNameArray.begin(); itr != m_SoundNameArray.end();){
			SAFE_DELETE(*itr);
			itr++;
		}
		m_SoundNameArray.clear();
	}

	LPCSTR FindName(LPCSTR name){
		int size = m_SoundNameArray.size();
		for (int idx = 0; idx < size; idx++){
			if (!strcmp(name,m_SoundNameArray[idx])){
				return m_SoundNameArray[idx];
			}
		}
		return nullptr;
	}
private:
	AUDIO_SET m_audio;	//XACT�f�[�^�p
	vector<LPCSTR> m_SoundNameArray;
};

//WaveBank����
