#ifndef CRUDETIMER_H
#define CRUDETIMER_H
//------------------------------------------------------------------------
//
//  ファイル名: CrudeTimer.h
//
//  概要: 秒単位で時間を計測するタイマー
//
//  作成者: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

// このライブラリをインクルードする必要がある
#pragma comment(lib, "winmm.lib")

#include <windows.h>

#define Clock CrudeTimer::Instance()

class CrudeTimer
{
private:


	// クラス生成時刻を秒単位で設定
	double m_dStartTime;

	// 開始時刻を設定
	CrudeTimer() { m_dStartTime = timeGetTime() * 0.001; }

	// コピーコンストラクターと代入演算子はprivateにする
	CrudeTimer(const CrudeTimer&);
	CrudeTimer& operator=(const CrudeTimer&);

public:

	static CrudeTimer* Instance();

	// タイマー開始後の経過時間を返す
	double getCurrentTime() { return timeGetTime() * 0.001 - m_dStartTime; }

};

#endif