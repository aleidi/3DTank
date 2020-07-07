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
//  see description in header
//------------------------------------------------------------------------
void MessageDispatcher::Discharge(AIController* pReceiverController,
	const Telegram& telegram)
{
	if (!pReceiverController->handleMessage(telegram))
	{
		//telegram could not be handled
		cout << "Message not handled";
	}
}

//---------------------------- DispatchMessage ---------------------------
//
//  given a message, a receiver, a sender and any time delay , this function
//  routes the message to the correct agent (if no delay) or stores
//  in the message queue to be dispatched at the correct time
//------------------------------------------------------------------------
void MessageDispatcher::Dispatch_Message(double  delay,
	int    sender,
	int    receiver,
	int    msg,
	void*  ExtraInfo)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	//get pointers to the sender and receiver
	//BaseGameEntity* pSender = EntityMgr->getEntityFromID(sender);
	//BaseGameEntity* pReceiver = EntityMgr->getEntityFromID(receiver);
	AIController* pSenderController = SceneManager::sGetInstance()->getAIController(sender);
	AIController* pReceiverController = SceneManager::sGetInstance()->getAIController(receiver);

	//make sure the receiver is valid
	if (pReceiverController == NULL)
	{
		cout << "\nWarning! No Receiver with ID of " << receiver << " found";

		return;
	}

	//create the telegram
	Telegram telegram(0, sender, receiver, msg, ExtraInfo);

	//if there is no delay, route telegram immediately                       
	if (delay <= 0.0f)
	{
		cout << "\nInstant telegram dispatched at time: " << Clock->getCurrentTime()
			<< " by " << getNameOfEntity(pSenderController->getID()) << " for " << getNameOfEntity(pReceiverController->getID())
			<< ". Msg is " << MsgToStr(msg);

		//send the telegram to the recipient
		Discharge(pReceiverController, telegram);
	}

	//else calculate the time when the telegram should be dispatched
	else
	{
		double CurrentTime = Clock->getCurrentTime();

		telegram.DispatchTime = CurrentTime + delay;

		//and put it in the queue
		PriorityQ.insert(telegram);

		cout << "\nDelayed telegram from " << getNameOfEntity(pSenderController->getID()) << " recorded at time "
			<< Clock->getCurrentTime() << " for " << getNameOfEntity(pReceiverController->getID())
			<< ". Msg is " << MsgToStr(msg);

	}
}


//---------------------- DispatchDelayedMessages -------------------------
//
//  This function dispatches any telegrams with a timestamp that has
//  expired. Any dispatched telegrams are removed from the queue
//------------------------------------------------------------------------
void MessageDispatcher::DispatchDelayedMessages()
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	//get current time
	double CurrentTime = Clock->getCurrentTime();

	//now peek at the queue to see if any telegrams need dispatching.
	//remove all telegrams from the front of the queue that have gone
	//past their sell by date
	while (!PriorityQ.empty() &&
		(PriorityQ.begin()->DispatchTime < CurrentTime) &&
		(PriorityQ.begin()->DispatchTime > 0))
	{
		//read the telegram from the front of the queue
		const Telegram& telegram = *PriorityQ.begin();

		//find the recipient
		//BaseGameEntity* pReceiver = EntityMgr->getEntityFromID(telegram.Receiver);
		AIController* pReceiverController = SceneManager::sGetInstance()->getAIController(telegram.Receiver);

		//send the telegram to the recipient
		Discharge(pReceiverController, telegram);

		//remove it from the queue
		PriorityQ.erase(PriorityQ.begin());
	}
}
