#pragma once

#include "control.h"
#include "sprite.h"

namespace cj {

enum CanvasType {cnvNone, cnvGDI, cnvWeb, cnvOpenGL};

class Canvas : public Control {
protected:
	bool isPaintRect;
	Rect paintRect;
	Point offset;
public:
	Point hintPos;
	bool isCalcPaintRect;
	CanvasType canvasType;
	Canvas(Control *owner);
	//Canvas(Control *owner, WndStyle style);

	virtual void line(Rect rect) = 0;
	virtual void rectangle(Rect rect) = 0;
	virtual void roundRect(Rect rect, int cornerW, int cornerH) = 0;
	virtual void ellipse(Rect rect) = 0;

	virtual void edgeRectangle(Rect rect) {}
	virtual void fillRectangle(Rect rect) {}
	virtual void edgeEllipse(Rect rect) {}
	virtual void fillEllipse(Rect rect) {}
	virtual void image(Rect rect, Bitmap *bmp) {}
	virtual void imageCenter(Rect rect, Bitmap *bmp) {}
	virtual Bitmap* createBitmap() { return NULL; }
	virtual void polyline(Rect rect, List *lstPoint) {}
	virtual void polygon(Rect rect, List *lstPoint) {}
	virtual void sprite(Rect rect, Sprite &sprite) {}


	virtual void grid(Rect rect) {}

	virtual void setFontId(int id) {}
	virtual int registerFont(Font *font) { return 0; }

	virtual Size getTextSize(String value) { return Size(); }
	virtual void text(Rect rect, String s) {}
	virtual void text(Point rect, String s) {}

	virtual void createGridRect(Size size) {}

	virtual void setCaption(String value) {}
	virtual void scissor(Rect rect) {}
	
	virtual Point getOffset();
	virtual void setOffset(Point value);
	virtual Rect getPaintRect();
	virtual void setPaintRect(Rect rect);
	virtual void releasePaintRect();
};



}
