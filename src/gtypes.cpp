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
void Color::set256(byte r, byte g, byte b)
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