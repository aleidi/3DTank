#pragma once

#pragma warning (disable:4786)

#include <set>

#include "ConsoleUtils.h"
#include "Telegram.h"

class AIController;

const double SEND_MSG_IMMEDIATELY = 0.0f;
const int NO_ADDITIONAL_INFO = 0;

#define Dispatch MessageDispatcher::getInstance()

class MessageDispatcher {
public:
	//このクラスはシングルトン
	static MessageDispatcher* getInstance();

	//別のエージェントへメッセージを送信する。受信側はIDで指定する。
	void Dispatch_Message(double  delay,
		int    sender,
		int    receiver,
		int    msg,
		void*  ExtraInfo);

	//遅延メッセージを送信する。このメソッドは
	//メインゲームループごとに呼び出す。
	void DispatchDelayedMessages();
private:
	std::set<Telegram> PriorityQ;

	void Discharge(AIController* pReceiver, const Telegram& msg);

	MessageDispatcher() {}

	//コピーコンストラクターと代入演算子はprivateにする
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);
};
