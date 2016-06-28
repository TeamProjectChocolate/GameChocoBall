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

typedef struct SOUND_DATA{
	char Name[FILENAME_MAX];
	void* Pointer;
};

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
	void PlayCue(const char*,bool,void*);

	//�L���[��~�֐�(�L���[��)
	void StopCue(const char*,bool,void*);

	void AddSound(LPCSTR name,void* pointer){
		SOUND_DATA* work = new SOUND_DATA;
		strcpy(work->Name, name);
		work->Pointer = pointer;
		m_SoundDataArray.push_back(work);
	}

	bool DeleteSound(LPCSTR name,void* pointer){
		for (vector<SOUND_DATA*>::iterator itr = m_SoundDataArray.begin(); itr != m_SoundDataArray.end();){
			if ((*itr)->Pointer == pointer){
				if (!strcmp(name, (*itr)->Name)){
					(*itr)->Pointer = nullptr;
					SAFE_DELETE(*itr);
					itr = m_SoundDataArray.erase(itr);
					return true;
				}
				else{
					itr++;
				}
			}
			else{
				itr++;
			}
		}
		return false;
	}

	void DeleteAll(){
		for (vector<SOUND_DATA*>::iterator itr = m_SoundDataArray.begin(); itr != m_SoundDataArray.end();){
			(*itr)->Pointer = nullptr;
			SAFE_DELETE(*itr);
			itr = m_SoundDataArray.erase(itr);
		}
		m_SoundDataArray.clear();
	}

	bool FindSound(LPCSTR name,void* pointer){
		int size = m_SoundDataArray.size();
		for (int idx = 0; idx < size; idx++){
			if (m_SoundDataArray[idx]->Pointer == pointer){
				if (!strcmp(name, m_SoundDataArray[idx]->Name)){
					return true;
				}
			}
		}
		return false;
	}
private:
	AUDIO_SET m_audio;	//XACT�f�[�^�p
	vector<SOUND_DATA*> m_SoundDataArray;
};

//WaveBank����
