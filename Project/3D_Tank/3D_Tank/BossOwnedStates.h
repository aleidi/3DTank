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
	float count = 0.0f;
};

class Missile : public State<AIController> {
public:
	static Missile* getInstance();
	virtual void enter(AIController* pETank);
	virtual void execute(AIController* pETank, float deltaTime);
	virtual void exit(AIController* pETank);

	virtual bool onMessage(AIController* agent, const Telegram& msg);
private:
	Missile() {}

	Missile(const Missile&);
	Missile& operator=(const Missile&);
	float count = 0.0f;
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
	float count = 0.0f;
};


