#include "cj.h"
#include "cjUI.h"

namespace cj {

//--------------------------------------------------------------------------------------------------
//----------          Класс Color          ---------------------------------------------------------
//--------------------------------------------------------------------------------------------------
Color::Color() {
	set(0, 0, 0);
}
Color::Color(real r, real g, real b)
{
	set(r, g, b);
}
void Color::set(Color C)
{
	r = C.r;
	g = C.g;
	b = C.b;
}
void Color::set(real r, real g, real b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}
void Color::get256(uchar &r, uchar &g, uchar &b) {
	real max = 255;
	r = this->r * max;
	g = this->g * max;
	b = this->b * max;
}
void Color::set256(uchar r, uchar g, uchar b)
{
	real max = 255;
	this->r = (real)r / max;
	this->g = (real)g / max;
	this->b = (real)b / max;
}
ulong Color::getRGB()
{
	real a = ((int)(r * 255)) + ((int)(g * 255)) * 256 + ((int)(b * 255)) * 65536;
	return (ulong)a;
}

}