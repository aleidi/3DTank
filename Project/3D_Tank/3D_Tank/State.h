#pragma once

struct Telegram;

template <class entity_type>
class State {
public:
	virtual ~State(){}
	virtual void enter(entity_type*) = 0;
	virtual void execute(entity_type*) = 0;
	virtual void exit(entity_type*) = 0;

	virtual bool onMessage(entity_type*, const Telegram&) = 0;
};

