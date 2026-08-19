#pragma once
//------------------------------------------------------------------------
//
//  ファイル名: Telegram.h
//
//  概要:   テレグラムを定義する。テレグラムはメッセージの送信に必要な
//          情報を記録するデータ構造であり、ゲームエージェント間の通信に
//          使用される。
//
//  作成者: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <iostream>
#include <math.h>


struct Telegram
{
	//このテレグラムの送信元エンティティ
	int          Sender;

	//このテレグラムの受信先エンティティ
	int          Receiver;

	//メッセージ本体。すべてのメッセージは次のファイルで列挙される
	//"MessageTypes.h"
	int          Msg;

	//メッセージは即時送信、または指定時間後に遅延送信できる。
	//遅延が必要な場合、このフィールドに送信予定時刻を
	//記録する。
	double       DispatchTime;

	//メッセージに付随する追加情報
	void*        ExtraInfo;


	Telegram() :DispatchTime(-1),
		Sender(-1),
		Receiver(-1),
		Msg(-1)
	{}


	Telegram(double time,
		int    sender,
		int    receiver,
		int    msg,
		void*  info = NULL) : DispatchTime(time),
		Sender(sender),
		Receiver(receiver),
		Msg(msg),
		ExtraInfo(info)
	{}

};


//テレグラムは優先度付きキューに格納されるため、キューが送信時刻順に
//並べ替えられるように > 演算子をオーバーロードする。
//2つのテレグラムを同一とみなすには、送信時刻の差が
//SmallestDelay未満である必要がある。
const double SmallestDelay = 0.25;


inline bool operator==(const Telegram& t1, const Telegram& t2)
{
	return (fabs(t1.DispatchTime - t2.DispatchTime) < SmallestDelay) &&
		(t1.Sender == t2.Sender) &&
		(t1.Receiver == t2.Receiver) &&
		(t1.Msg == t2.Msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2)
	{
		return false;
	}

	else
	{
		return  (t1.DispatchTime < t2.DispatchTime);
	}
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
{
	os << "time: " << t.DispatchTime << "  Sender: " << t.Sender
		<< "   Receiver: " << t.Receiver << "   Msg: " << t.Msg;

	return os;
}

//TelegramのExtraInfoフィールドを必要な型として参照するための
//補助関数。
template <class T>
inline T DereferenceToType(void* p)
{
	return *(T*)(p);
}

