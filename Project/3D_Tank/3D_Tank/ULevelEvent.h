#pragma once

#include "UIEvent.h"

class GameLevelBase;

class ULevelEvent : public UIEvent
{
public:
	ULevelEvent() = delete;
	ULevelEvent(GameLevelBase* level) : mLevel(level)
	{}
	virtual ~ULevelEvent() {}

	virtual void onClick() override {}
	virtual void onPressed() override {}

protected:
	GameLevelBase* mLevel;
};

class UStartEvent : public ULevelEvent
{
public:
	UStartEvent(GameLevelBase* level) :ULevelEvent(level) {}

	void onClick() override;
};

class USetEvent : public ULevelEvent
{
public:
	USetEvent(GameLevelBase* level) : ULevelEvent(level) {}

	void onClick() override;
};


class UExitEvent : public ULevelEvent
{
public:
	UExitEvent(GameLevelBase* level) : ULevelEvent(level) {}

	void onClick() override;
};

class UGmeModeEvent : public ULevelEvent
{
public:
	UGmeModeEvent(GameLevelBase* level) : ULevelEvent(level) {}
	void onClick() override;
	void onPressed() override {}
};

class UEditModeEvent : public ULevelEvent
{
public:
	UEditModeEvent(GameLevelBase* level) : ULevelEvent(level) {}
	void onClick() override;
	void onPressed() override {}
};

class UCNEvent : public ULevelEvent
{
public:
	UCNEvent(GameLevelBase* level) : ULevelEvent(level) {};
	void onClick() override;
	
	void onPressed() override {}
};

class UENEvent : public ULevelEvent
{
public:
	UENEvent(GameLevelBase* level) : ULevelEvent(level) {};
	void onClick() override;
	
	void onPressed() override {}
};

class UShutDownEvent : public UIEvent
{
public:
	void onClick() override;
	
	void onPressed() override {}
};

class UReturnEvent : public ULevelEvent
{
public:
	UReturnEvent(GameLevelBase* level) : ULevelEvent(level) {}

	void onClick() override;
};

class UCancelEvent : public ULevelEvent
{
public:
	UCancelEvent(GameLevelBase* level) : ULevelEvent(level) {}

	void onClick() override;
};

