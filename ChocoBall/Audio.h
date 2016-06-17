#pragma once
#include "xact3.h"

typedef struct AUDIO_SET{
	IXACT3Engine* pEngine;	//XACTエンジン
	IXACT3WaveBank* pWaveBank;  //ウェーブバンク
	IXACT3SoundBank* pSoundBank;	//サウンドバンク
	const char* xactEngineName;	//XACTエンジン名
	const char* waveBankName;   //ウェーブバンク名
	const char* soundBankName;	//サウンドバンク名
	VOID* pbWaveBank;           //ウェーブバンクハンドル
	VOID* pbSoundBank; // サウンドバンクハンドル
	XACTINDEX cueIndex;                //キューインデックス

}AOUDI_SET;

//XACT初期化
class CAudio{
public:
	CAudio();
	~CAudio();
	//XACT初期化関数（エンジン名、ウェーブバンク名、サウンドバンク名)
	HRESULT Initialize(const char*, const char*, const char*);
	//エンジン作成
	HRESULT CreateEngine(const char*);
	//ウェーブバンク作成
	HRESULT CreateWaveBank(const char*);
	//サウンドバンク作成
	HRESULT CreateSoundBank(const char*);
	//XACTエンジンの周期的タスク実行用
	void Run();
	//XACT終了関数
	void CleanupXACT();

	//キュー再生関数(キュー名)
	//引き数:const char*型 サウンド名
	//		 bool型 音を重ねて再生するかのフラグ(trueなら重ねる,falseなら重ねない)
	void PlayCue(const char*,bool);

	//キュー停止関数(キュー名)
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
	AUDIO_SET m_audio;	//XACTデータ用
	vector<LPCSTR> m_SoundNameArray;
};

//WaveBank生成
