#include "states/console.h"
#include "drawing.h"
#include "globals.h"
#include "engineMethods.h"
#include "enumerations.h"

#include <iostream>

#define ClassName StateConsole

ClassName* ClassName::_thisInstance = nullptr;

ClassName::~ClassName()
{
	Cleanup();
}

void ClassName::Initialize()
{
	_isOpenBig = false;
	_isOpenSmall = false;

	_consoleColor = {0, 50, 50, 255};
	_textColor = {255, 255, 255, 255};
	
	// This is how open the console is in terms of pixels
	_openHeight = 0;
	// This is a fraction of the screen height;
	_openHeightBig = 0.75;	
	// This is a fraction of openHeight;
	_openHeightSmall = 0.3;
	// This is a fraction of how fast the console opens
	_openRate = 0.04;

	ParseCommand("This is a nice test string! abcdefghijklmnopqrstuvwxyz");
	ParseCommand("Second test");
	ParseCommand("Third, final test");
}

void ClassName::Cleanup()
{

}

int ClassName::HandleEvents(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			Close();
			break;

		case SDLK_BACKQUOTE:
			{
				//std::cout << "CONSOLE DETECTED BACKQUOTE" << std::endl;
				bool lshift = event->key.keysym.mod & KMOD_LSHIFT;

				if (_isOpenBig)
				{
					if (lshift) Close();
					else Open(false);
				}
				else if (_isOpenSmall)
				{
					if (!lshift) Close();
					else Open(true);
				}
				else
				{
					Open(event->key.keysym.mod & KMOD_LSHIFT);
					//if (event->key.keysym.mod == KMOD_LSHIFT) {
					//	_isOpenBig = true;
					//	_isOpenSmall = false;
					//} else {
					//	_isOpenSmall = true;
					//	_isOpenBig = false;
					//}
				}
			}
			break;

		case SDLK_BACKSPACE:
			{
			if (_currentLine.size() > 0)
				_currentLine.pop_back();
			}
			break;

		case SDLK_RETURN:
			{
			if (_currentLine.size() > 0)
				ParseCommand(_currentLine);
				_currentLine = "";
			}
			break;
		}
	}
	else if (event->type == SDL_TEXTINPUT)
	{
		_currentLine += event->text.text;
	}
	//else if (event->type == SDL_TEXTEDITING)
	//{


	//}

	//if (IsClosed()) return CLOSE_CONSOLE;

	return -1;
}

void ClassName::Update()
{
	int rate = SCREEN_HEIGHT * _openHeightBig * _openRate;

	if (_isOpenBig || _isOpenSmall)
	{
		if (_isOpenBig)
		{
			int maxHeight = SCREEN_HEIGHT * _openHeightBig;
			Lerp<int>(_openHeight, maxHeight, rate);
		}
		else if (_isOpenSmall)
		{
			int maxHeight = SCREEN_HEIGHT * _openHeightSmall;
			Lerp<int>(_openHeight, maxHeight, rate);
		}
	}
	else if (_openHeight > 0) {
		Lerp<int>(_openHeight, 0, rate);
	}

	if (/*!SDL_IsTextInputActive() && */IsOpen())
	{
		//std::cout << "Starting text input..." << std::endl;
		SDL_StartTextInput();
	}
}

void ClassName::Render(float interpolation)
{
	if (_openHeight > 0) {
		DrawRect(0, 0, SCREEN_WIDTH, _openHeight, _consoleColor);
	}

	for (int i = 0; i < _history.size(); i++)
	{
		// First drop shadow, then text
		DrawText(_history[i], consoleFont, 8 + 1, _openHeight - 64 - (16 * i) + 1, ALIGN_LEFT, {0, 0, 0, 255});
		DrawText(_history[i], consoleFont, 8, _openHeight - 64 - (16 * i), ALIGN_LEFT, _textColor);
	}

	// Also draw current line being typed
	if (_currentLine != "") {
		DrawText(_currentLine, consoleFont, 8 + 1, _openHeight - 32 + 1, ALIGN_LEFT, {0, 0, 0, 255});
		DrawText(_currentLine, consoleFont, 8, _openHeight - 32, ALIGN_LEFT, _textColor);
	}

    //_entities.RenderAll(interpolation);
}

void ClassName::Open(bool big)
{
	if (big) {
		_isOpenBig = true;
		_isOpenSmall = false;
	} else {
		_isOpenSmall = true;
		_isOpenBig = false;
	}

	_openHeight += (SCREEN_HEIGHT * _openHeightBig) * _openRate;
}

void ClassName::Close()
{
	_isOpenSmall = false;
	_isOpenBig = false;

	//if (SDL_IsTextInputActive())
	//{
	SDL_StopTextInput();
	//}
}

void ClassName::ParseCommand(std::string str)
{
	_history.insert(_history.begin(), str);
}

bool ClassName::IsOpen()
{
	//std::cout << "_openHeight\t\t" << _openHeight << std::endl;
	//std::cout << "_openHeightSmall\t\t" << SCREEN_HEIGHT * _openHeightSmall << std::endl;
	//std::cout << "_openHeightBig\t\t" << SCREEN_HEIGHT * _openHeightBig << std::endl;
	if (_isOpenSmall && _openHeight == static_cast<int>(SCREEN_HEIGHT * _openHeightSmall)) 
	{
		//std::cout << "IsOpenSmall" << std::endl;
		return true;
	}
   	if (_isOpenBig && _openHeight == static_cast<int>(SCREEN_HEIGHT * _openHeightBig))
	{
		//std::cout << "IsOpenBig" << std::endl;
		return true;
	}

	return false;
}

bool ClassName::IsClosed()
{
	return (_openHeight == 0 && !_isOpenBig && !_isOpenSmall);
}

#ifdef ClassName
#undef ClassName
#endif
