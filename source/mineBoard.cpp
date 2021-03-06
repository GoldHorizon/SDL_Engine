#include "mineBoard.h"
#include "drawing.h"

#include <math.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <algorithm>

MineBoard::MineBoard()
{
	_board = nullptr;

	_boardWidth = 0;
	_boardHeight = 0;

	_bombCount = 0;
	_tilesLeft = 0;
	_flagCount = 0;

	_generated = false;
	_ended = false;
}

MineBoard::~MineBoard()
{
	ClearBoard();
}

void MineBoard::HandleEvents(SDL_Event* e)
{
}

void MineBoard::Update()
{
	//if (_board != nullptr)
	//{
	//	for (int j = 0; j < _boardHeight; j++) {
	//		for (int i = 0; i < _boardWidth; i++) {
	//			//std::cout << "::: " << xOffset << std::endl;
	//			GetTile(i, j).Update();
	//		}
	//	}
	//}
}

void MineBoard::Render(float interpolation, int xOffset, int yOffset)
{
	if (_board != nullptr)
	{
		for (int j = 0; j < _boardHeight; j++) {
			for (int i = 0; i < _boardWidth; i++) {
				//std::cout << "::: " << xOffset << std::endl;
				GetTile(i, j).Render(interpolation, this->x + xOffset + (i * 32), this->y + yOffset + (j * 32));
			}
		}

		DrawText(std::to_string(std::max(_bombCount - _flagCount, 0)), TextQuality::SHADED, defaultFont, 8, 8, TextAlignment::ALIGN_LEFT, {255, 255, 255});
	}
}

void MineBoard::CreateBoard(int sizex, int sizey)
{
	// Clear the board if it already exists
	ClearBoard();

	// Create new board
	_boardWidth = sizex;
	_boardHeight = sizey;

	_board = new MineTile [_boardWidth * _boardHeight]; // Create tile array
	_tilesLeft = _boardWidth * _boardHeight;
}

void MineBoard::GenerateBombs(int startx, int starty)
{
	std::srand(time(NULL));

	// Generate bombs
	for (int j = 0; j < _boardHeight; j++) {
		for (int i = 0; i < _boardWidth; i++) {
			int num = static_cast<int>(rand() % 5);

			if (num == 0)	{
				GetTile(i, j).SetBomb(true); // Set tile to have bomb
				_bombCount++;
			}
			else {
				GetTile(i, j).SetBomb(false); // Set tile to be clear
			}
		}
	}

	// Clear starting position(s) (Should ALWAYS happen)
	if (startx >= 0 && startx < _boardWidth && starty >= 0 && starty < _boardHeight) {
		for (int j = starty - 1; j <= starty + 1; j++) {
			for (int i = startx - 1; i <= startx + 1; i++) {
				if (i >= 0 && i < _boardWidth
				 && j >= 0 && j < _boardHeight
				 && GetTile(i, j).bomb()) {
					GetTile(i, j).SetBomb(false); // Set tile to be clear
					_bombCount--;
				}
			}
		}
	}
	else {
		std::cout << "Error: Invalid starting position of minesweeper board!" << std::endl;
	}

	_generated = true;
}

void MineBoard::SetTileCounters()
{
	// Set adjacent bomb count of each tiles
	for (int j = 0; j < _boardHeight; j++) {
		for (int i = 0; i < _boardWidth; i++) {
			if (GetTile(i, j).bomb() == false) {
				int minx, miny, maxx, maxy;
				if (i == 0) 				minx = i; else minx = i - 1; 
				if (j == 0) 				miny = j; else miny = j - 1; 
				if (i == _boardWidth - 1)  	maxx = i; else maxx = i + 1; 
				if (j == _boardHeight - 1) 	maxy = j; else maxy = j + 1; 

				int count = 0;
				for (int yy = miny; yy <= maxy; yy++) {
					for (int xx = minx; xx <= maxx; xx++) {
						if (GetTile(xx, yy).bomb()) count++;
					}
				}

				if (count > 0) GetTile(i, j).SetCount(count);
			}
		}
	}
}

void MineBoard::ClickTile(int x, int y)
{
	if (GetTile(x, y).flagged() || GetTile(x, y).clicked()) return;

	// If tile is bomb, we lose and end game
	if (GetTile(x, y).bomb()) {
		//_bombCount--;
		_ended = true;
		RevealBoard();
	}

	GetTile(x, y).SetClicked(true);
	_tilesLeft--;

	// If tile is empty, reveal surrounding squares too
	if (!GetTile(x, y).bomb() && GetTile(x, y).count() == 0) {
		// Check all surrounding tiles
		for (int j = y - 1; j <= y + 1; j++) {
			for (int i = x - 1; i <= x + 1; i++) {
				if (i >= 0 && i < _boardWidth && j >= 0 && j < _boardHeight
					&& GetTile(i, j).clicked() == false)
					ClickTile(i, j);
			}
		}
	}

	// If we reveal all tiles that aren't bombs, we win!
	if (_tilesLeft == _bombCount) {
		_ended = true;
	}
}

void MineBoard::FlagTile(int x, int y)
{
	if (_generated && !_ended) {
		GetTile(x, y).SetFlagged(!GetTile(x, y).flagged());

		if (GetTile(x, y).clicked()) return;

		if (GetTile(x, y).flagged()) {
			_flagCount++;
		} else {
			_flagCount--;
		}
	}
}

void MineBoard::ClearBoard()
{
	if (_board != nullptr) delete [] _board;

	_bombCount = 0;
	_tilesLeft = 0;
	_flagCount = 0;

	_generated = false;
	_ended = false;
}

MineTile& MineBoard::GetTile(int x, int y)
{
	return _board[_boardWidth * y + x];
}

void MineBoard::RevealBoard()
{
	for (int j = 0; j < _boardHeight; j++) {
		for (int i = 0; i < _boardWidth; i++) {
			if (!GetTile(i, j).clicked() && GetTile(i, j).bomb()) {
				GetTile(i, j).RevealTile();
			}
		}
	}
	_ended = true;
}

void MineBoard::InitTestBoard(int startx, int starty, int sizex, int sizey)
{
	CreateBoard(sizex, sizey);
	GenerateBombs(startx, starty);
	SetTileCounters();
}

void MineBoard::PrintTestBoard()
{
	for (int j = 0; j < _boardHeight; j++) {
		for (int i = 0; i < _boardWidth; i++) {
			if (GetTile(i, j).bomb())
				std::cout << "*";
			else if (GetTile(i, j).count() == 0)
				std::cout << ".";
			else
				std::cout << GetTile(i, j).count();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int MineBoard::width()
{
	return _boardWidth;
}

int MineBoard::height()
{
	return _boardHeight;
}

bool MineBoard::generated()
{
	return _generated;
}

bool MineBoard::ended()
{
	return _ended;
}

