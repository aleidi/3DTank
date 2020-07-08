#pragma once
// all states that can be assigned to the enemytank class
#include "State.h"

class AIController;
struct Telegram;

class Alert : public State<AIController> {
public:
	static Alert* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank, float deltaTime);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Alert() {}

	Alert(const Alert&);
	Alert& operator=(const Alert&);
};

class Battle : public State<AIController> {
public:
	static Battle* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank, float deltaTime);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Battle() {}

	Battle(const Battle&);
	Battle& operator=(const Battle&);
	int normalshot = 0;
	float offset = 0.0f;
};

class StageTwo : public State<AIController> {
public:
	static StageTwo* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank, float deltaTime);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	StageTwo() {}

	StageTwo(const StageTwo&);
	StageTwo& operator=(const StageTwo&);
	int normalshot = 0;
	float offset = 0.0f;
	float superCount = 0.0f;
	bool particleSwitch = true;
};

class Violent : public State<AIController> {
public:
	static Violent* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank, float deltaTime);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Violent() {}

	Violent(const Violent&);
	Violent& operator=(const Violent&);
	float superCount = 0.0f;
	bool particleSwitch = true;
};


