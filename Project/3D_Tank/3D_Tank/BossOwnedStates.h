#pragma once
// all states that can be assigned to the enemytank class
#include "State.h"

class AIController;
struct Telegram;

class Rest : public State<AIController> {
public:
	static Rest* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank, float deltaTime);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Rest() {}

	Rest(const Rest&);
	Rest& operator=(const Rest&);
};


