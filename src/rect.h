#pragma once

namespace cj {

class Size;

class Point : public Object //Класс точка
{
public:
	real x;
	real y;
	real z;

	Point();
	Point(real x, real y, real z = 0);
	Point(Point *point);

	void set(Point &value);
	void set(real AX, real AY, real z = 0);
	void incPos(Point p);
	void incPos(Size sz);
	void decPos(Point p);
	void decPos(Size sz);
};

class Size : public Object //Класс размер
{
public:
	real w;//Ширина
	real h;//Высота
	real t;//Толщина

	Size();
	Size(real w, real h, real t = 0);

	void set(Size &sz);
	void set(real w, real h, real t = 0);
};

class Rect : public Object {
public:
	Point pos;
	Size size;
	Rect();
	Rect(Point pos, Size size);
	Rect(Point point1, Point point2);
	Rect(real x1, real y1, real x2, real y2, bool b = false);
	Rect(real x, real y, real z, real w, real h, real t);

	virtual void setBounds(real x, real y, real w, real h);

	virtual Rect getRect();
	virtual void setRect(real x1, real y1, real x2, real y2);
	virtual Size getSize();
	virtual void setSize(Size value);

	virtual void set(Rect &r);
	virtual void set(Point pos, Size size);
	virtual void set(Point point1, Point point2);
	virtual void set(real x1, real y1, real x2, real y2, bool b);
	virtual void set(real x, real y, real z, real w, real h, real t);

	virtual real getW();
	virtual void setW(real width);
	virtual real getH();
	virtual void setH(real height);
	virtual real getT();
	virtual void setT(real height);
	virtual real getWidth();
	virtual void setWidth(real width);
	virtual real getHeight();
	virtual void setHeight(real height);

	virtual real getX1();
	virtual void setX1(real value);
	virtual real getY1();
	virtual void setY1(real value);
	virtual real getX2();
	virtual void setX2(real value);
	virtual real getY2();
	virtual void setY2(real value);

	virtual Point getCenter();
	virtual Point getEnd();

	virtual void incPos(Point pos);
	virtual void decPos(Point pos);
	virtual Point getPos();
	virtual void setPos(Point pos);
	virtual void setPos(real x, real y);
	virtual void incEnd(Point pos);
	virtual void decEnd(Point pos);
	virtual void setEnd(Point pos);
	virtual void changeRect(real x1, real y1, real x2, real y2);

	bool into(real x, real y);
	bool into(Rect rect);

	virtual void correct();
};

}
