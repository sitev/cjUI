#pragma once

namespace cj {

class Color : public Object
{
public:
	real r, g, b;
	Color();
	Color(real r, real g, real b);
	virtual void set(Color c);
	virtual void set(real r, real g, real b);

	virtual void get256(uchar &r, uchar &g, uchar &b);
	virtual void set256(uchar r, uchar g, uchar b);

	virtual ulong getRGB();
};

class Bitmap : public Size
{
public:
	Bitmap() {}
	virtual bool loadFromFile(String fileName) = 0;
};

}