#pragma once

class GameStateBase;
class Pawn;
class ControllerBase;

class GameModeBase
{
public:
	GameModeBase();
	virtual ~GameModeBase();

	virtual void onInit();
	virtual void onUpdate(float deltaTime);

	void setGameState(GameStateBase* gameState) noexcept;
	void setPlayer(Pawn* player) noexcept;
	void setPlayerController(ControllerBase* playerController) noexcept;
	Pawn* getPlayer() const;
	ControllerBase* getPlayerController() const;

public:
	static GameModeBase* MainGameMode;

protected:
	GameStateBase* mGameState;
	Pawn* mPlayer;
	ControllerBase* mPlayerController;
};
