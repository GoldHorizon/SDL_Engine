#pragma once

#include "gameState.h"
#include "level.h"
#include "text.h"
#include "event.h"

#define ClassName StateEditor

enum class EditMode {
	CAMERA,
	SELECTING,
	CREATING,
	DELETING,
	MOVING,
};

class StateEditor : public GameState
{
	/*
	 * Constructors/Destructors
	 */
public:
	ClassName() {
		Initialize();
		SetType(GameStateType::LEVEL_EDITOR); 
		Resume(); 
	}
	~ClassName();

	/*
	 * Class Methods
	 */
	void Initialize();
	void Cleanup();

	KeyEvent HandleEvents(Event&);
	void Update();
	void Render(float interpolation);

	void SaveLevel();
	bool LoadLevel();
	void SetLevel(std::string name);
	void SetLevel(Level* level);
	Level* GetLevel();

	void ResetLevel();

private:
	Level _currentLevel;

	std::string _levelName;
	// Editing values
	bool _drawGrid;
	int _gridSize;
	EditorEntityType _entityType;
	bool _drawType;

	//Text _textType; // @Todo: may have to reuse this

	// Entity mode
	bool _isCreating = false;	// Creating entities on mouse
	bool _isDeleting = false;	// Deleting entities on mouse
	bool _isSelecting = false;	// Box/Click selection
	bool _isMoving = false;		// Selected entitites

	// Editor vars
	EditMode _primaryMode = EditMode::SELECTING;
	EditMode _secondaryMode = EditMode::DELETING;
	bool _primaryActive = false;
	bool _secondaryActive = false;
	bool _cameraActive = false;
	bool _drawHUD = true;

	int _moveDiffx = 0;
	int _moveDiffy = 0;

	vec2<int> _selectionStart;
	int _selectionTimer;

	void CreateUI();
	void SelectEntities(int x, int y, int w, int h);

	// Editor entity struct
	struct EditorEnt {
		std::unique_ptr<Entity>* entPtr;

		bool _locked = false;
		bool _hidden = false;
		bool _selected = false;
		bool _grabbed = false;

		EditorEnt(std::unique_ptr<Entity>& ep) : entPtr(&ep) {};
	};

	std::vector<std::unique_ptr<EditorEnt>> _levelEntities;
};

#ifdef ClassName
#undef ClassName
#endif
