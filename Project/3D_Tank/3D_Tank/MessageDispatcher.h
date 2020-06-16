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
	//this class is a singleton
	static MessageDispatcher* getInstance();

	//send a message to another agent. Receiving agent is referenced by ID.
	void Dispatch_Message(double  delay,
		int    sender,
		int    receiver,
		int    msg,
		void*  ExtraInfo);

	//send out any delayed messages. This method is called each time through   
	//the main game loop.
	void DispatchDelayedMessages();
private:
	std::set<Telegram> PriorityQ;

	void Discharge(AIController* pReceiver, const Telegram& msg);

	MessageDispatcher() {}

	//copy ctor and assignment should be private
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);
};
