#include "camera.h"
#include "globals.h"

Camera::Camera()
{
	_origin = Align::TOP_L;
	_x = 0;
	_y = 0;
	_w = SCREEN_WIDTH;
	_h = SCREEN_HEIGHT;

	_moveToTarget = false;
	_targetObj = nullptr;
	_targetPos = {0, 0};
}

Camera::~Camera()
{

}

/*
 * Class Methods
 */
void Camera::Move(int x, int y)
{
	if (!_moveToTarget) {
		_x += x;
		_y += y;
	//} else {
	//	_targetPos.x += x;
	//	_targetPos.y += y;
	}
}

void Camera::Move(vec2<int> pos)
{
	if (!_moveToTarget) {
		_x += pos.x;
		_y += pos.y;
	//} else {
	//	_targetPos += pos;
	}
}

/*
 * Get Methods
 */
int Camera::x() const
{
	return _x;
}
int Camera::y() const
{
	return _y;
}
int Camera::w() const
{
	return _w;
}
int Camera::h() const
{
	return _h;
}
vec2<int> Camera::position() const
{
	return vec2<int> (_x, _y);
}

vec2<int> Camera::dimensions() const
{
	return vec2<int> (_w, _h);
}

Align Camera::origin() const
{
	return _origin;
}

/*
 * Set Methods
 */
void Camera::SetX(int x)
{
	if (_origin == Align::TOP_L || _origin == Align::MID_L || _origin == Align::BOT_L)
		_x = x;

	if (_origin == Align::TOP_C || _origin == Align::MID_C || _origin == Align::BOT_C)
		_x = x - (_w / 2);

	if (_origin == Align::TOP_R || _origin == Align::MID_R || _origin == Align::BOT_R)
		_x = x - _w;
}

void Camera::SetY(int y)
{
	if (_origin == Align::TOP_L || _origin == Align::TOP_C || _origin == Align::TOP_R)
		_y = y;

	if (_origin == Align::MID_L || _origin == Align::MID_C || _origin == Align::MID_R)
		_y = y - (_h / 2);

	if (_origin == Align::BOT_L || _origin == Align::BOT_C || _origin == Align::BOT_R)
		_y = y - _h;
}

void Camera::SetW(int w)
{
	_w = w;
}

void Camera::SetH(int h)
{
	_h = h;
}

void Camera::SetPosition(int x, int y)
{
	if (!_moveToTarget) {
		SetX(x);
		SetY(y);
	//} else {
	//	_targetPos.x = x;
	//	_targetPos.y = y;
	}
}

void Camera::SetPosition(vec2<int> pos)
{
	if (!_moveToTarget) {
		SetX(pos.x);
		SetY(pos.y);
	//} else {
	//	_targetPos.x = pos.x;
	//	_targetPos.y = pos.y;
	}
}

void Camera::SetDimensions(int w, int h)
{
	_w = w;
	_h = h;
}

void Camera::SetDimensions(vec2<int> dim)
{
	_w = dim.x;
	_h = dim.y;
}

void Camera::SetOrigin(Align origin)
{
	_origin = origin;
}

