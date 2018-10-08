#include "panel.h"
#include "drawing.h"

#include <iostream>

Panel::Panel()
{
	_title = "Title";
	_dim = {128, 512};
	_barHeight = 24;

	_bgColor = {0, .2, .2, .9};
	_barColor = {0, .6, .6, .9};
}

Panel::~Panel()
{

}

void Panel::HandleEvents(SDL_Event* event)
{
	
}

void Panel::Update()
{

}

void Panel::Render(float interpolation, int xOffset, int yOffset)
{

}

void Panel::RenderCustom(float interpolation, int xOffset, int yOffset)
{
	// Draw window
	DrawRect(this->x(), this->y(), _dim.x, _dim.y, _bgColor);
	DrawRect(this->x(), this->y(), _dim.x, _barHeight, _barColor);
	
	// Draw title text
	DrawSmoothText(_title, consoleFont, (x() + _dim.x / 2) + 1, (y() + (_barHeight - 20) / 2) + 1, TextAlignment::ALIGN_CENTER, {0, 0, 0, 1});
	DrawSmoothText(_title, consoleFont, x() + _dim.x / 2, y() + (_barHeight - 20) / 2, TextAlignment::ALIGN_CENTER, {1, 1, 1, 1});
}

std::string Panel::title()
{
	return _title;
}

vec2<int> Panel::dim()
{
	return _dim;
}

vec4<float> Panel::bgColor()
{
	return _bgColor;
}

vec4<float> Panel::barColor()
{
	return _barColor;
}

void Panel::SetTitle(std::string title)
{
	_title = title;
}

void Panel::SetPos(vec2<int> dim)
{
	_dim = dim;
}

void Panel::SetBgColor(vec4<float> color)
{
	_bgColor = color;
}

void Panel::SetBarColor(vec4<float> color)
{
	_barColor = color;
}

