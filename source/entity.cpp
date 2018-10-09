#include "entity.h"
#include "globals.h"
#include "constants.h"
#include "engineMethods.h"

#include <iostream>
#include <math.h>
//#include <filesystem>

#include "SDL_image.h"

Entity::Entity() : Entity(globalRenderer)
{
}

Entity::Entity(SDL_Renderer* renderer):
	//_image(nullptr),
	//_imagePath("nopath"),
	//_renderer(renderer),
	_name("noname"),
	_ID(0),
	_active(true),
	_visible(true),
	_x(0),
	_y(0),
	_depth(0),
	_direction(0),
	_speed(0),
	_hspeed(0),
	_vspeed(0)
	//_imageAlpha(1),
	//_imageAngle(0),
	//_imageWidth(0),
	//_imageHeight(0),
	//_spriteDimensions({ 0, 0 }),
	//_imageSpeed(0),
	//_imageTimer(0),
	//_lastImageTime(0),
	//_imageIndex(0)
{
	//_imageOrigin = {0, 0};

	//if (renderer == nullptr)
	//{
	//	std::cerr << "Error: Cannot instantiate object - globalRenderer not set!" << std::endl;
	//}
}

Entity::~Entity()
{
	FreeMemory();
}

void Entity::LoadImage(const std::string file, int spriteWidth, int spriteHeight)
{
	_image.LoadFromFile(file, spriteWidth, spriteHeight);
}

void Entity::LoadImage(SDL_Surface* surface)
{
	_image.LoadFromSurface(surface);
}

void Entity::FreeMemory()
{
	_image.FreeMemory();
}

void Entity::HandleEvents(Event& event)
{

}

void Entity::Update()
{
	float xdir = (cos(direction() * PI / 180) * speed());
	float ydir = (sin(direction() * PI / 180) * speed());

	Move(xdir, ydir);

	_image.Update();
}

void Entity::Render(float interpolation, int xOffset, int yOffset)
{
	// Only attempt to render if we have successfully loaded an image and it is visible
	if (_visible)
	{
		// Create a set of ints to use for drawing position (use interpolation to predict movement)
		int xx = static_cast<int>(_x) + xOffset
			+ static_cast<int>(cos(_direction * PI / 180) * _speed * (_active * interpolation));
		int yy = static_cast<int>(_y) + yOffset
			+ static_cast<int>(sin(_direction * PI / 180) * _speed * (_active * interpolation));

		_image.Draw(xx, yy);

		RenderCustom(interpolation, xOffset, yOffset);
	}
}

//void Entity::Render(SDL_Rect* clipping)
//{
//	if (_image != nullptr)
//	{
//		// Create a set of ints to use for drawing position
//		int xx = static_cast<int>(_x) - _imageOrigin.x;
//		int yy = static_cast<int>(_y) - _imageOrigin.y;
//
//		// Create a rectangle to put on display
//		SDL_Rect displayImage = {xx, yy, _imageWidth, _imageHeight};
//
//		// If we are clipping the sprite, adjust it
//		if (clipping != nullptr)
//		{
//			displayImage.w = clipping->w;
//			displayImage.h = clipping->h;
//		}
//
//		SDL_RenderCopyEx(_renderer, _image, clipping, &displayImage, _imageAngle, &_imageOrigin, SDL_FLIP_NONE);
//	}
////	else
////	{
////		//std::cout << "Error: _image not found..." << std::endl;
////	}
//}

//void Entity::Render(SDL_RendererFlip flip, SDL_Rect* clipping)
//{
//	if (_image != nullptr)
//	{
//		// Create a set of ints to use for drawing position
//		int xx = static_cast<int>(_x) - _imageOrigin.x;
//		int yy = static_cast<int>(_y) - _imageOrigin.y;
//
//		// Create a rectangle to put on display
//		SDL_Rect displayImage = {xx, yy, _imageWidth, _imageHeight};
//
//		// If we are clipping the sprite, adjust it
//		if (clipping != nullptr)
//		{
//			displayImage.w = clipping->w;
//			displayImage.h = clipping->h;
//		}
//
//		SDL_RenderCopyEx(_renderer, _image, clipping, &displayImage, _imageAngle, &_imageOrigin, flip);
////		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
////		SDL_RenderDrawRect(_renderer, &displayImage);
//	}
////	else
////	{
////		//std::cout << "Error: _image not found..." << std::endl;
////	}
//}

//void Drawable::Render(float x, float y, double angle, SDL_Point* origin, SDL_RendererFlip flip, SDL_Rect* clipping)
//{
//	// Set our member variables to the new drawing position
//	_x = x;
//	_y = y;
//
//	if (_image != nullptr)
//	{
//		// Create a set of ints to use for drawing position
//		int xx = static_cast<int>(x);
//		int yy = static_cast<int>(y);
//
//		// Create a rectangle to put on display
//		SDL_Rect displayImage = {xx, yy, _width, _height};
//		//std::cout << clipping->x << " " << clipping->y << " " << clipping->w << " " << clipping->h << " " << std::endl;
//
//		// If we are clipping the sprite, adjust it
//		if (clipping != nullptr)
//		{
//			displayImage.w = clipping->w;
//			displayImage.h = clipping->h;
//		}
//
//		SDL_RenderCopyEx(_renderer, _image, clipping, &displayImage, angle, origin, flip);
//	}
////	else
////	{
////		//std::cout << "Error: _image not found..." << std::endl;
////	}
//}

void Entity::Move(float x, float y)
{
	_x += x;
	_y += y;
}

Entity* Entity::NewInstance()
{
	return nullptr;
}

std::string Entity::Serialize()
{
	std::string serialize_string;

	serialize_string = "@Entity ";
	serialize_string += "\"" + _name + "\"" + " "
		+ std::to_string(_active) + " "
		+ std::to_string(_visible) + " "
		+ std::to_string(_x) + " "
		+ std::to_string(_y) + " "
		+ std::to_string(_depth) + " "
		+ std::to_string(_direction) + " "
		+ std::to_string(_speed) + " "
		+ std::to_string(_hspeed) + " "
		+ std::to_string(_vspeed) + " ";
		//+ std::to_string(_imageAlpha) + " "
		//+ std::to_string(_imageAngle) + " "
		//+ std::to_string(_imageWidth) + " "
		//+ std::to_string(_imageHeight) + " "
		//+ std::to_string(_imageSpeed) + " "
		//+ std::to_string(_imageTimer) + " "
		//+ std::to_string(_lastImageTime) + " "
		//+ std::to_string(_imageIndex) + " "
		//+ std::to_string(_imageOrigin.x) + " "
		//+ std::to_string(_imageOrigin.y) + " "
		//+ std::to_string(_spriteDimensions.x) + " "
		//+ std::to_string(_spriteDimensions.y) + " ";

	return serialize_string;
}

void Entity::Unserialize(std::string str)
{
	sVector* list = ParseSerializedString(str);

	int index = 0;

	while ((*list)[index] != "@Entity" && index < list->size())
		index++;

	if ((*list)[index++] == "@Entity")
	{
		//_imagePath 			= (*list)[index++];
		_name 				= (*list)[index++];
		_active 			= (*list)[index++] == "1" ? true : false;	
		_visible 			= (*list)[index++] == "1" ? true : false;	
		_x					= std::stof((*list)[index++]);	
		_y					= std::stof((*list)[index++]);
		_depth 				= std::stof((*list)[index++]);
		_direction 			= std::stof((*list)[index++]);
		_speed 				= std::stof((*list)[index++]);
		_hspeed 			= std::stof((*list)[index++]);
		_vspeed 			= std::stof((*list)[index++]);
		//_imageAlpha 		= std::stof((*list)[index++]);
		//_imageAngle 		= std::stod((*list)[index++]);
		//_imageWidth 		= std::stoi((*list)[index++]);
		//_imageHeight 		= std::stoi((*list)[index++]);
		//_imageSpeed 		= std::stoi((*list)[index++]);
		//_imageTimer 		= std::stoi((*list)[index++]);
		//_lastImageTime 		= std::stoi((*list)[index++]);
		//_imageIndex 		= std::stoi((*list)[index++]);
		//_imageOrigin.x 		= std::stoi((*list)[index++]);
		//_imageOrigin.y 		= std::stoi((*list)[index++]);
		//_spriteDimensions.x = std::stoi((*list)[index++]);
		//_spriteDimensions.y = std::stoi((*list)[index++]);
	}

	delete list;

}

/*
 * Get Methods
 */
Image* Entity::image()
{
	return &_image;
}

//SDL_Renderer* Entity::renderer() const
//{
//	return _renderer;
//}

std::string Entity::name() const
{
	return _name;
}
int Entity::ID() const
{
	return _ID;
}
bool Entity::active() const
{
	return _active;
}
bool Entity::visible() const
{
	return _visible;
}
float Entity::x() const
{
	return _x;
}
float Entity::y() const
{
	return _y;
}
float Entity::depth() const
{
	return _depth;
}
float Entity::direction() const
{
	return _direction;
}
float Entity::speed() const
{
	return _speed;
}
float Entity::hspeed() const
{
	return _hspeed;
}
float Entity::vspeed() const
{
	return _vspeed;
}
//float Entity::imageAlpha() const
//{
//	return _imageAlpha;
//}
//double Entity::imageAngle() const
//{
//	return _imageAngle;
//}
//SDL_Point Entity::imageOrigin() const
//{
//	return _imageOrigin;
//}
//int Entity::imageWidth() const
//{
//	return _imageWidth;
//}
//int Entity::imageHeight() const
//{
//	return _imageHeight;
//}
//int Entity::imageSpeed() const
//{
//	return _imageSpeed;
//}
//int Entity::imageIndex() const
//{
//	return _imageIndex;
//}
//SDL_Point Entity::spriteDimensions() const
//{
//	return _spriteDimensions;
//}

/*
 * Set Methods
 */
void Entity::SetName(std::string name)
{
	if (name != "")
	{
		_name = name;
	}
	else
	{
		_name = "noname";
	}
}
void Entity::SetID(int ID)
{
	_ID = ID;
}
void Entity::SetActive(bool active)
{
	_active = active;
}
void Entity::SetVisible(bool visible)
{
	_visible = visible;
}
void Entity::SetX(float x)
{
	_x = x;
}
void Entity::SetY(float y)
{
	_y = y;
}
void Entity::SetDepth(float depth)
{
	_depth = depth;
}
void Entity::SetDirection(float direction)
{
	_direction = direction;

	while(_direction >= 360)
	{
		_direction -= 360;
	}
	while(_direction < 0)
	{
		_direction += 360;
	}

	// Change hspeed/vspeed
	_hspeed = cos(_direction * PI / 180) * _speed;
	_vspeed = sin(_direction * PI / 180) * _speed;
}
void Entity::SetSpeed(float speed)
{
	if (_speed != 0)
	{
		float diff = speed / _speed;

		// Change hspeed/vspeed
		_hspeed *= diff;
		_vspeed *= diff;
	}
	else
	{
		_hspeed = cos(_direction * PI / 180) * speed;
		_vspeed = sin(_direction * PI / 180) * speed;
	}

	_speed = speed;
}
void Entity::SetHSpeed(float hspeed)
{
	_hspeed = hspeed;

	// Change speed/direction
	CalculateSpeedDir();
}
void Entity::SetVSpeed(float vspeed)
{
	_vspeed = vspeed;

	// Change speed/direction
	CalculateSpeedDir();
}
//void Entity::SetImageAlpha(float alpha)
//{
//	_imageAlpha = alpha;
//	if (SDL_SetTextureAlphaMod(_image, (int)(_imageAlpha * 255)) != 0)
//	{
//		std::cout << IMG_GetError() << std::endl;
//	}
//}
//void Entity::SetImageAngle(double angle)
//{
//	_imageAngle = angle;
//}
//void Entity::SetImageOrigin(int x, int y)
//{
//	_imageOrigin.x = x;
//	_imageOrigin.y = y;
//}
//void Entity::SetImageOrigin(SDL_Point pos)
//{
//	_imageOrigin.x = pos.x;
//	_imageOrigin.y = pos.y;
//}
//void Entity::SetImageSpeed(int speed)
//{
//	_imageSpeed = speed;
//}
//void Entity::SetImageIndex(int index)
//{
//	_imageIndex = index;
//}

void Entity::SetPosition(float x, float y)
{
	_x = x;
	_y = y;
}
void Entity::SetPosition(SDL_Point pos)
{
	_x = pos.x;
	_y = pos.y;
}

void Entity::CalculateSpeedDir()
{
	// Change speed/direction
	if (_hspeed != 0)
	{
		_direction = atan(_vspeed / _hspeed) / PI * 180;
		if (_hspeed > 0)
		{
			//_direction = 180 - _direction;
		}
		else
		{
			_direction = 180 + _direction;
		}
	}
	else
	{
		if (_vspeed > 0)
		{
			_direction = 90;
		}
		else if (_vspeed < 0)
		{
			_direction = 270;
		}
	}

	while (_direction >= 360)
	{
		_direction -= 360;
	}
	while (_direction < 0)
	{
		_direction += 360;
	}

	_speed = sqrt(pow(_hspeed, 2) + pow(_vspeed, 2));
}

//void Entity::AdvanceImage()
//{
//	_imageTimer += SDL_GetTicks() - _lastImageTime;
//
//	_lastImageTime = SDL_GetTicks();
//
//	// If imageSpeed is positive, we progress forwards through animation
//	if (_imageSpeed > 0)
//	{
//		if (_imageTimer > _imageSpeed)
//		{
//			//_imageTimer -= _imageSpeed;
//			_imageTimer %= _imageSpeed;
//			_imageIndex++;
//		}
//	}
//	// If imageSpeed is negative, we step backwards through animation
//	else if (_imageSpeed < 0)
//	{
//		if (_imageTimer > abs(_imageSpeed))
//		{
//			//_imageTimer -= abs(_imageSpeed);
//			_imageTimer %= abs(_imageSpeed);
//			_imageIndex--;
//		}
//	}
//	// If imageSpeed is 0 reset timer and do nothing
//	else
//	{
//		_imageTimer = 0;
//	}
//
//	// If we overflow on imageIndex, go back to beginning
//	while (_imageIndex >= (_imageWidth / _spriteDimensions.x))
//	{
//		_imageIndex -= (_imageWidth / _spriteDimensions.x);
//	}
//	// If we underflow imageIndex, go to end
//	while (_imageIndex < 0)
//	{
//		_imageIndex += (_imageWidth / _spriteDimensions.x);
//	}
//
//	// DEBUG
//	//std::cout << _imageTimer << std::endl;
//}

bool operator<(const Entity &el, const Entity &er)
{
	return el._depth < er._depth;
}
bool operator>(const Entity &el, const Entity &er)
{
	return el._depth > er._depth;
}
bool operator<=(const Entity &el, const Entity &er)
{
	return el._depth <= er._depth;
}
bool operator>=(const Entity &el, const Entity &er)
{
	return el._depth >= er._depth;
}
bool operator==(const Entity &el, const Entity &er)
{
	return el._depth == er._depth;
}
bool operator!=(const Entity &el, const Entity &er)
{
	return el._depth != er._depth;
}
