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
	void PlayCue(const char*);

	//キュー停止関数(キュー名)
	void StopCue(const char*);

private:
	AUDIO_SET m_audio;	//XACTデータ用
};

//WaveBank生成
