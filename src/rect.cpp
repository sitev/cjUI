#include "cj.h"
#include "cjUI.h"

namespace cj {

//--------------------------------------------------------------------------------------------------
//----------          Класс Point          ---------------------------------------------------------
//--------------------------------------------------------------------------------------------------
Point::Point() {
	x = y = z = 0;
}
Point::Point(real x, real y, real z) {
	set(x, y, z);
}
Point::Point(Point *point) {
	set(*point);
}
void Point::set(Point &value) {
	x = value.x;
	y = value.y;
}
void Point::set(real x, real y, real z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
void Point::incPos(Point p) {
	x += p.x;
	y += p.y;
	z += p.z;
}
void Point::incPos(Size sz) {
	x += sz.w;
	y += sz.h;
	z += sz.t;
}
void Point::decPos(Point p) {
	x -= p.x;
	y -= p.y;
	z -= p.z;
}
void Point::decPos(Size sz) {
	x -= sz.w;
	y -= sz.h;
	z -= sz.t;
}



//--------------------------------------------------------------------------------------------------
//----------          Класс Size          ----------------------------------------------------------
//--------------------------------------------------------------------------------------------------
Size::Size() {
	w = 0;
	h = 0;
	t = 0;
}
Size::Size(real w, real h, real t) {
	set(w, h, t);
}
void Size::set(Size &sz) {
	w = sz.w;
	h = sz.h;
	t = sz.t;
}
void Size::set(real w, real h, real t) {
	this->w = w;
	this->h = h;
	this->t = t;
}

//--------------------------------------------------------------------------------------------------
//----------          Класс Rect          ----------------------------------------------------------
//--------------------------------------------------------------------------------------------------
Rect::Rect() {
	set(0, 0, 0, 0, false);
}
Rect::Rect(Point pos, Size size) {
	set(pos, size);
}
Rect::Rect(Point point1, Point point2) {
	set(point1, point2);
}
Rect::Rect(real x1, real y1, real x2, real y2, bool b) {
	set(x1, y1, x2, y2, b);
}
Rect::Rect(real x, real y, real z, real w, real h, real t) {
	set(x, y, z, w, h, t);
}
void Rect::setBounds(real x, real y, real w, real h) {
	pos.set(x, y);
	size.set(w, h);
}
Rect Rect::getRect() {
	return *this;
}
void Rect::setRect(real x1, real y1, real x2, real y2) {
	setBounds(x1, y1, x2 - x1, y2 - y1);
}
Size Rect::getSize() {
	return size;
}
void Rect::setSize(Size value) {
	//size = value;
	setBounds(pos.x, pos.y, value.w, value.h);
}

void Rect::set(Rect &r) {
	setBounds(r.pos.x, r.pos.y, r.size. w, r.size.h);
}
void Rect::set(Point pos, Size size) {
	setBounds(pos.x, pos.y, size.w, size.h);
}
void Rect::set(Point point1, Point point2) {
	setRect(point1.x, point1.y, point2.x, point2.y);
}
void Rect::set(real x1, real y1, real x2, real y2, bool b) {
  if (!b)
  {
    setRect(x1, y1, x2, y2);
  }
  else
  {
    setRect(x1, y1, x1 + x2, y1 + y2);
  }
}
void Rect::set(real x, real y, real z, real w, real h, real t) {
	this->pos.x = x;
	this->pos.y = y;
	this->pos.z = z;
	this->size.w = w;
	this->size.h = h;
	this->size.t = t;
}

real Rect::getW() {
	return size.w;
}
void Rect::setW(real w) {
	size.w = w;
}
real Rect::getH() {
	return size.h;
}
void Rect::setH(real h) {
	size.h = h;
}
real Rect::getT() {
	return size.t;
}
void Rect::setT(real t) {
	size.t = t;
}
real Rect::getWidth() {
	return getW();
}
void Rect::setWidth(real width) {
	setW(width);
}
real Rect::getHeight() {
	return getH();
}
void Rect::setHeight(real height) {
	setH(height);
}
real Rect::getX1() {
	return pos.x;
}
void Rect::setX1(real value) {
	pos.x = value;
}
real Rect::getY1() {
	return pos.y;
}
void Rect::setY1(real value) {
	pos.y = value;
}
real Rect::getX2() {
	return pos.x + size.w;
}
void Rect::setX2(real value) {
	size.w = value - pos.x;
}
real Rect::getY2() {
	return pos.y + size.h;
}
void Rect::setY2(real value) {
	size.h = value - pos.y;
}
Point Rect::getCenter() {
	Point p(pos);
	p.x += size.w / 2;
	p.y += size.h / 2;
	p.z += size.t / 2;
	return p;
}
Point Rect::getEnd() {
	return Point(pos.x + size.w, pos.y + size.h, pos.z + size.t);
}
void Rect::incPos(Point pos) {
	pos.incPos(this->pos);
	set(pos, size);
}
void Rect::decPos(Point pos) {
	pos.decPos(this->pos);
	set(pos, size);
}
Point Rect::getPos() {
	return pos;
}
void Rect::setPos(Point pos) {
	set(pos, size);
}
void Rect::setPos(real x, real y) {
	setPos(Point(x, y));
}
void Rect::incEnd(Point pos) {
	size.w = size.w + pos.x;
	size.h = size.h + pos.y;
	size.t = size.t + pos.z;
}
void Rect::decEnd(Point pos) {
	size.w = size.w - pos.x;
	size.h = size.h - pos.y;
	size.t = size.t - pos.z;
}
void Rect::setEnd(Point pos) {
	size.w = pos.x - this->pos.x;
	size.h = pos.y - this->pos.y;
	size.t = pos.z - this->pos.z;
}
void Rect::changeRect(real x1, real y1, real x2, real y2) {

}
bool Rect::into(real x, real y) {
	Rect r = *this;
	if (r.pos.x <= x && r.pos.y <= y && r.getEnd().x >= x && r.getEnd().y >= y) return true;
	return false;
}
bool Rect::into(Rect rect) {
	Rect r2 = rect;
	Rect r1 = *this;
	if (r1.getX1() <= r2.getX1() && r1.getY1() <= r2.getY1() &&	
		r1.getX2() >= r2.getX2() && r1.getY2() >= r2.getY2()) return true;
	return false;
}

void Rect::correct() {
	if (size.w < 0) {
		pos.x += size.w;
		size.w = -size.w;
	}
	if (size.h < 0) {
		pos.y += size.h;
		size.h = -size.h;
	}
}

}
