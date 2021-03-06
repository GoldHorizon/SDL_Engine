#pragma once

#include <vector>
#include <memory>

#include "entityCollection.h"
#include "enumerations.h"
#include "event.h"
#include "file.h"
#include "states/console.h"

#include "SDL.h"

class GameState;
enum class GameStatus;

class Game
{
public:
	/*
	* Constructors/Destructors
	*/
	Game();
	~Game();

	/*
	* Class Methods
	*/
	// Initialize()			- Initialize SDL and other game necessities
	GameStatus Initialize();

	// ChangeState()		- Changes state to specified state
	//	newState:		new state to change to
	GameState* ChangeState(GameStateType type);

	// PushState()          - Push another state onto the stack of states
	GameState* PushState(GameStateType type);

	// PopState()           - Pop the latest state from the top of the stack
	void PopState();

	// GetState()			- Get the latest state, or the latest of a specific type
	GameState* GetState(GameStateType type = GameStateType::NONE);

	// GetInput()			- Retrieves global window input, returns quit value
	GameStatus GetInput();

	// Update()				- Updates entire game by one frame
	void Update();

	// Render()				- Renders game with interpolation
	//	interpolation:	how much to predict in advance
	void Render(float interpolation);

	// Entities()			- General function, returns main entity collection
	EntityCollection& Entities();

	// CloseConsole()		- Closes the console, if it is open
	void CloseConsole();

	// QuitGame()			- Quits the game
	void QuitGame();

private:
	// LoadFonts()			- Load used fonts into memory
	void LoadFonts();

	// _mainWindow		- main window to render to
	SDL_Window* _mainWindow;
	// _mainRenderer	- main renderer, renders to _mainWindow
	SDL_Renderer* _mainRenderer;
	// _event			- global event gathered by game
	Event _event;

	// _stateStack      - stack of all states in game
	std::vector<std::unique_ptr<GameState>> _stateStack;

	// _console			- persistent console in the game
	StateConsole _console;

	// _entities		- collection of game entities
	EntityCollection _entities;

	// _playing		- whether the game is still being played (running)
	bool _playing;

	// _varFile		- file containing game variables
	File _varFile;
};

enum class GameStatus 
{
	initialized,
	running,
	halted,
	stopped,
	error
};
