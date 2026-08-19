#include "MessageDispatcher.h"
#include "BaseGameEntity.h"
#include "CrudeTimer.h"
// #include "EntityManager.h"
#include "MessageTypes.h"
#include "EntityNames.h"
#include "AIController.h"
#include "SceneManager.h"
#include <iostream>
using std::cout;

using std::set;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------ Instance -------------------------------------

MessageDispatcher* MessageDispatcher::getInstance()
{
	static MessageDispatcher m_MessageDispatcher;

	return &m_MessageDispatcher;
}


//----------------------------- Dispatch ---------------------------------
//  
//  説明はヘッダーを参照
//------------------------------------------------------------------------
void MessageDispatcher::Discharge(AIController* pReceiverController,
	const Telegram& telegram)
{
	if (pReceiverController == NULL)
	{
		return;
	}

	if (!pReceiverController->handleMessage(telegram))
	{
		//Telegramを処理できなかった
		cout << "Message not handled";
	}
}

//---------------------------- DispatchMessage ---------------------------
//
//  メッセージ、受信者、送信者、遅延時間を受け取り、
//  遅延がなければ対象エージェントへ送信し、遅延があれば
//  適切な時刻に送信するためメッセージキューへ格納する
//------------------------------------------------------------------------
void MessageDispatcher::Dispatch_Message(double  delay,
	int    sender,
	int    receiver,
	int    msg,
	void*  ExtraInfo)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	//送信者と受信者のポインターを取得
	//BaseGameEntity* pSender = EntityMgr->getEntityFromID(sender);
	//BaseGameEntity* pReceiver = EntityMgr->getEntityFromID(receiver);
	AIController* pSenderController = SceneManager::sGetInstance()->getAIController(sender);
	AIController* pReceiverController = SceneManager::sGetInstance()->getAIController(receiver);

	//受信者が有効か確認
	if (pReceiverController == NULL)
	{
		cout << "\nWarning! No Receiver with ID of " << receiver << " found";

		return;
	}

	//Telegramを作成
	Telegram telegram(0, sender, receiver, msg, ExtraInfo);

	//遅延がなければTelegramを即時送信
	if (delay <= 0.0f)
	{
		cout << "\nInstant telegram dispatched at time: " << Clock->getCurrentTime()
			<< " by " << getNameOfEntity(pSenderController->getID()) << " for " << getNameOfEntity(pReceiverController->getID())
			<< ". Msg is " << MsgToStr(msg);

		//受信者へTelegramを送信
		Discharge(pReceiverController, telegram);
	}

	//遅延があればTelegramの送信時刻を計算
	else
	{
		double CurrentTime = Clock->getCurrentTime();

		telegram.DispatchTime = CurrentTime + delay;

		//キューへ格納
		PriorityQ.insert(telegram);

		cout << "\nDelayed telegram from " << getNameOfEntity(pSenderController->getID()) << " recorded at time "
			<< Clock->getCurrentTime() << " for " << getNameOfEntity(pReceiverController->getID())
			<< ". Msg is " << MsgToStr(msg);

	}
}


//---------------------- DispatchDelayedMessages -------------------------
//
//  送信時刻を迎えたTelegramを送信する。
//  送信済みのTelegramはキューから削除する
//------------------------------------------------------------------------
void MessageDispatcher::DispatchDelayedMessages()
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	//現在時刻を取得
	double CurrentTime = Clock->getCurrentTime();

	//キューを確認し、送信が必要なTelegramを調べる。
	//送信時刻を過ぎたTelegramを
	//キューの先頭からすべて取り出す
	while (!PriorityQ.empty() &&
		(PriorityQ.begin()->DispatchTime < CurrentTime) &&
		(PriorityQ.begin()->DispatchTime > 0))
	{
		//キュー先頭のTelegramを取得
		const Telegram& telegram = *PriorityQ.begin();

		//受信者を検索
		//BaseGameEntity* pReceiver = EntityMgr->getEntityFromID(telegram.Receiver);
		AIController* pReceiverController = SceneManager::sGetInstance()->getAIController(telegram.Receiver);

		//受信者へTelegramを送信
		if (pReceiverController != NULL)
		{
			Discharge(pReceiverController, telegram);
		}
		else
		{
			cout << "\nWarning! Delayed telegram receiver destroyed. Receiver ID = " << telegram.Receiver;
		}

		//キューから削除
		PriorityQ.erase(PriorityQ.begin());
	}
}
