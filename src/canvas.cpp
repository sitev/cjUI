#include "cj.h"
#include "cjUI.h"

namespace cj {

//--------------------------------------------------------------------------------------------------
//----------          Класс Canvas          --------------------------------------------------------
//--------------------------------------------------------------------------------------------------

Canvas::Canvas(Control *owner) : Control(owner) {
	canvas = this;
	isCanvas = true;
	paintRect = Rect(0, 0, 0, 0, false);
	isPaintRect = isCalcPaintRect = false;
	hintPos.set(0, 0);
}
Point Canvas::getOffset() {
	return offset;
}
void Canvas::setOffset(Point value) {
	offset = value;
}
Rect Canvas::getPaintRect() { 
	return paintRect; 
}
void Canvas::setPaintRect(Rect rect) {
	isPaintRect = true;
	paintRect = rect;
}
void Canvas::releasePaintRect() {
	isPaintRect = false;
	paintRect = Rect(0, 0, 0, 0, false);
}




}
