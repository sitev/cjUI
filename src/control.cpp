#include "cj.h"
#include "cjUI.h"

namespace cj {

//--------------------------------------------------------------------------------------------------
//----------          Класс ShiftKeys          -----------------------------------------------------
//--------------------------------------------------------------------------------------------------
ShiftKeys::ShiftKeys() {
	shift = alt = ctrl = false;
}

//--------------------------------------------------------------------------------------------------
//----------          Класс Anchors          -------------------------------------------------------
//--------------------------------------------------------------------------------------------------

Anchors::Anchors() {

}
Anchors::Anchors(int x1, int y1, int x2, int y2) {
	set(x1, y1, x2, y2);
}
Anchors Anchors::operator=(Anchors value) {
	x1 = value.x1;
	y1 = value.y1;
	x2 = value.x2;
	y2 = value.y2;
	return *this;
}
void Anchors::set(int x1, int y1, int x2, int y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

//--------------------------------------------------------------------------------------------------
//----------          Класс Control          -------------------------------------------------------
//--------------------------------------------------------------------------------------------------

Control::Control(Control *owner) : Rect() {
	this->owner = owner;
	isCanvas = false;
	lstControl = new List();
	client = this;
	visible = true;
	jointed = false;
	stretch = true;
	isScissor = true;
	canvas = NULL;
	hint = "";
	if (owner != NULL)
	{
		owner->lstControl->add(this);
		canvas = owner->canvas;
	}

	set(0, 0, 100, 100, false);
	penWidth = 1;
	penStyle = psSolid;
	brushStyle = bsSolid;
	color = Color(1, 1, 1);

	///this->setObjectName(application->mngName->generateName());
}
Control::~Control() {
}
String Control::getClassName() {
	return "Control";
}
Control* Control::getOwner() {
	return owner;
}
void Control::setOwner(Control *owner) {
	this->owner = owner;
}
Canvas* Control::getCanvas() {
	return canvas;
}
void Control::setCanvas(Canvas *canvas) {
	this->canvas = canvas;
}
void Control::recalc(Rect rect) {
}
void Control::paintControl(Rect rect) {
	if (!visible) return;
	recalc(rect);
	paintBegin(rect);
	paint(rect);
	paintInner(rect);
	canvas->setPaintRect(rect);
	paintOuter(rect);
	
	paintTrackBegin(rect);
	paintTrack(rect);
	paintTrackEnd(rect);

	canvas->setPaintRect(rect);
	paintEnd(rect);
}
void Control::paintBegin(Rect &rect) {
	if (!visible) return;
	if (canvas == NULL) canvas = getCanvas();
	if (canvas == NULL) return;
/*
	saveRect = rect;
	try {
		canvas->setOffset(Point(0, 0));
	}
	catch (...) {
		canvas->setOffset(Point(0, 0));
	}
*/
	Rect r = getAbsoluteRect();
	rect = rect1AndRect2(rect, r);
	canvas->isScissor = this->isScissor;
	canvas->setPaintRect(rect);
}
void Control::paint(Rect rect) {
}
void Control::paintInner(Rect rect) {
	if (!visible) return;
	int count = 0;
	if (JControls_Exist()) count = JControls_GetCount();
	for (int i = 0; i < count; i++)	{
		Control *c = JControls_GetItem(i);
		String S = c->getObjectName();
		if (c != NULL) {
			c->paintControl(rect);
		}
	}
}
void Control::paintOuter(Rect rect) {
	if (!visible) return;
	int count = 0;
	if (UControls_Exist()) count = UControls_GetCount();
	for (int i = 0; i < count; i++)
	{
		Control *C = UControls_GetItem(i);
		string S = C->getClassName().to_string();
		String sName = C->getObjectName();
		Rect R = *C;
		if (C != NULL) {
			C->paintControl(rect);
		}
	}
}
void Control::paintTrackBegin(Rect &rect) {
/*    canvas->setOffset(Point(0, 0));

    if (owner == NULL) canvas->scissor(Rect(0, 0, 800, 600, false));
    else canvas->scissor(owner->getAbsoluteRect());
*/
}
void Control::paintTrack(Rect &rect) {
//  if (Track != NULL && Track->visible) Track->Paint();
	int count = UControls_GetCount();
	for (int i = 0; i < count; i++)
	{
		Control *c = UControls_GetItem(i);
		c->paintTrackBegin(rect);
		c->paintTrack(rect);
		c->paintTrackEnd(rect);
	}
}
void Control::paintTrackEnd(Rect &rect) {
}
void Control::paintEnd(Rect rect) {
/*
if (!visible) return;
	rect = saveRect;
	canvas->setPaintRect(rect);
*/
	canvas->releasePaintRect();
}
void Control::repaint() {
    if (canvas == NULL) return;
    canvas->repaint();
    return;
}

void Control::changeRect(real x1, real y1, real x2, real y2)
{
  Rect rect = *this;
  rect.pos.x += x1;
  rect.pos.y += y1;
  rect.size.w += x2 - x1;
  rect.size.h += y2 - y1;
  set(rect);
}

bool Control::getVisible() {
	return visible;
}

void Control::setVisible(bool value) {
	visible = value;
}

void Control::setColor(Color c) {
	color = c;
}
void Control::setColor(real r, real g, real b) {
	color.set(r, g, b);
}
void Control::setPenWidth(int value) {
	penWidth = value;
}
void Control::setPenStyle(PenStyle value) {
	penStyle = value;	
}
void Control::setBrushStyle(BrushStyle value) {
	brushStyle = value;
}
Point Control::getAbsoluteOffset() { 
	if (owner != NULL) return owner->getAbsolutePos();
	return Point(0, 0);
}
Point Control::getAbsolutePos() { 
	if (isCanvas) return Point(0, 0);
	Control *myOwner = owner;
	Point absPos = pos;
	while (myOwner != NULL && !myOwner->isCanvas) {
		absPos.incPos(myOwner->pos);
		myOwner = myOwner->owner;
	}
/*

	Point absPos = pos;
//	if (isCanvas) absPos.set(0, 0);
	Point ownerAbsPos(0, 0);
	if (owner) 
		ownerAbsPos = owner->getAbsolutePos();
	absPos.incPos(ownerAbsPos);
*/
	return absPos;
}
Rect Control::getAbsoluteRect() { 
	return Rect(getAbsolutePos(), size);
}

String Control::getFontName() {
#ifdef OS_WINDOWS
	///Font *f = application->mngFont->getFont(0);
	///return f->fontName;
#endif

#ifdef OS_LINUX
#endif
	return "";
}
void Control::setFontName(String value) {
}
Point Control::getOffset() {
//	if (canvas) 
//		return canvas->getOffset();
	return Point(0, 0);
}
/*
void Control::setOffset(Point value) {
	if (canvas) canvas->setOffset(value);
}
*/
int Control::indexOf()
{
    if (owner == NULL) return -1;
    int index = owner->JControls_IndexOf(this);
    if (index >= 0) return index;
    return owner->UControls_IndexOf(this);
}
void Control::joint(bool value)
{
	jointed = value;
}
bool Control::JControls_Exist()
{
  return lstControl != NULL;
}
int Control::JControls_GetCount()
{
    if (lstControl == NULL) return 0;
    int count = lstControl->getCount();
    int MyCount = 0;
    for (int i = 0; i < count; i++) {
        Control *C = (Control*)lstControl->getItem(i);
        if (C->jointed) MyCount++;
    }
    return MyCount;
}
int Control::JControls_GetControlsIndex(int index)
{
    if (lstControl == NULL) return -1;
    int count = lstControl->getCount();
    int idx = -1;
    for (int i = 0; i < count; i++) {
        Control *C = (Control*)lstControl->getItem(i);
        if (C->jointed) idx++;
        if (idx == index) return i;
    }
    return -1;
}
int Control::JControls_GetJControlsIndex(int index)
{
    if (lstControl == NULL) return -1;
    int count = lstControl->getCount();
    int idx = -1;
    for (int i = 0; i < count; i++) {
        Control *C = (Control*)lstControl->getItem(i);
        if (C->jointed) idx++;
        if (index == i) return idx;
    }
    return -1;
}
void Control::JControls_Add(Control* Item)
{
    if (lstControl == NULL)
    {
        lstControl = new List();
    }
    lstControl->add(Item);
    Item->jointed = true;
}
void Control::JControls_Insert(int index, Control* Item)
{
    if (lstControl == NULL)
    {
        lstControl = new List();
    }
    int idx = JControls_GetControlsIndex(index);
    lstControl->insert(idx, Item);
    Item->jointed = true;
}
Control* Control::JControls_GetItem(int index)
{
	if (lstControl == NULL) return NULL;
	int idx = JControls_GetControlsIndex(index);
	Control *c = (Control*)lstControl->getItem(idx);
	return c;
}
void Control::JControls_SetItem(int index, Control* data)
{
    if (lstControl == NULL) return;
    int idx = JControls_GetControlsIndex(index);
    lstControl->setItem(idx, data);
}
void Control::JControls_Change(int index1, int index2)
{
    if (lstControl == NULL) return;
    int idx1 = JControls_GetControlsIndex(index1);
    int idx2 = JControls_GetControlsIndex(index2);
    lstControl->change(idx1, idx2);
}
void Control::JControls_Delete(int index)
{
    if (lstControl == NULL) return;
    int idx = JControls_GetControlsIndex(index);
    lstControl->remove(idx);
}
void Control::JControls_DeleteLight(int index)
{
    if (lstControl == NULL) return;
    int idx = JControls_GetControlsIndex(index);
    lstControl->del(idx);
}
int Control::JControls_IndexOf(Control* Item)
{
    if (lstControl == NULL) return -1;
    int index = lstControl->indexOf(Item);
    int idx = JControls_GetJControlsIndex(index);
    return idx;
}
int Control::JControls_Remove(Control* Item)
{
    if (lstControl == NULL) return -1;
    int A = lstControl->remove(Item);
    if (JControls_GetCount() == 0)
    {
        delete lstControl;
        lstControl = NULL;
    }
    return A;
}
int Control::JControls_RemoveLight(Control* Item)
{
  if (lstControl == NULL) return -1;
  int A = lstControl->del(Item);
  if (JControls_GetCount() == 0)
  {
    delete lstControl;
    lstControl = NULL;
  }
  return A;
}
void Control::JControls_Clear()
{
    if (lstControl == NULL) return;
    int count = lstControl->getCount();
    for (int i = count - 1; i >= 0; i--) {
        lstControl->remove(i);
    }
}
void Control::JControls_ClearLight()
{
    if (lstControl == NULL) return;
    int count = lstControl->getCount();
    for (int i = count - 1; i >= 0; i--) {
        lstControl->del(i);
    }
}
bool Control::UControls_Exist()
{
  return lstControl != NULL;
}
int Control::UControls_GetCount()
{
    if (lstControl == NULL) return 0;
    int count = lstControl->getCount();
    int MyCount = 0;
    for (int i = 0; i < count; i++) {
        Control *C = (Control*)lstControl->getItem(i);
        if (!C->jointed) MyCount++;
    }
    return MyCount;
}
int Control::UControls_GetControlsIndex(int index)
{
    if (lstControl == NULL) return -1;
    int count = lstControl->getCount();
    int idx = -1;
    for (int i = 0; i < count; i++) {
        Control *C = (Control*)lstControl->getItem(i);
        if (!C->jointed) idx++;
        if (idx == index) return i;
    }
    return -1;
}
int Control::UControls_GetUControlsIndex(int ControlsIndex)
{
    if (lstControl == NULL) return -1;
    int count = lstControl->getCount();
    int index = -1;
    for (int i = 0; i < count; i++) {
        Control *C = (Control*)lstControl->getItem(i);
        if (!C->jointed) index++;
        if (ControlsIndex == i) return index;
    }
    return -1;
}
void Control::UControls_Add(Control* Item)
{
    if (lstControl == NULL)
    {
        lstControl = new List();
    }
    lstControl->add(Item);
    Item->jointed = false;
}
void Control::UControls_Insert(int index, Control* Item)
{
    if (lstControl == NULL)
    {
        lstControl = new List();
    }
    int idx = UControls_GetControlsIndex(index);
    lstControl->insert(idx, Item);
    Item->jointed = false;
}
Control* Control::UControls_GetItem(int index)
{
    if (lstControl == NULL) return NULL;
    int idx = UControls_GetControlsIndex(index);
    Control *c = (Control*)lstControl->getItem(idx);
	return c;
}
void Control::UControls_SetItem(int index, Control* data) {
    if (lstControl == NULL) return;
    int idx = UControls_GetControlsIndex(index);
    lstControl->setItem(idx, data);
}
void Control::UControls_Change(int index1, int index2) {
	Control *data1 = UControls_GetItem(index1);
	Control *data2 = UControls_GetItem(index2);
	UControls_SetItem(index1, data2);
	UControls_SetItem(index2, data1);

	/*
    if (lstControl == NULL) return;
    int index1 = UControls_GetControlsIndex(Index1);
    int index2 = UControls_GetControlsIndex(Index2);
    lstControl->change(index1, index2);
	*/
}
void Control::UControls_Delete(int index)
{
    if (lstControl == NULL) return;
    int idx = UControls_GetControlsIndex(index);
    lstControl->remove(idx);
}
void Control::UControls_DeleteLight(int index)
{
    if (lstControl == NULL) return;
    int idx = UControls_GetControlsIndex(index);
    lstControl->del(idx);
}
int Control::UControls_IndexOf(Control* Item)
{
    if (lstControl == NULL) return -1;
    int index = lstControl->indexOf(Item);
    int idx = UControls_GetUControlsIndex(index);
    return idx;
}
int Control::UControls_Remove(Control* Item)
{
    if (lstControl == NULL) return -1;
    int A = lstControl->remove(Item);
    /*
    if (UControls_GetCount() == 0)
    {
        delete lstControl;
        lstControl = NULL;
    }
    */
	Item = NULL;
    return A;
}
int Control::UControls_RemoveLight(Control* Item)
{
  if (lstControl == NULL) return -1;
  int A = lstControl->del(Item);
  if (UControls_GetCount() == 0)
  {
    delete lstControl;
    lstControl = NULL;
  }
  return A;
}
void Control::UControls_Clear()
{
    if (lstControl == NULL) return;
    int count = lstControl->getCount();
    for (int i = count - 1; i >= 0; i--) {
        lstControl->remove(i);
    }
}
void Control::UControls_ClearLight()
{
    if (lstControl == NULL) return;
    int count = UControls_GetCount();//lstControl->getCount();
    for (int i = count - 1; i >= 0; i--) {
		UControls_DeleteLight(i);
//        lstControl->del(i);
    }
}

void Control::inverseJointAll() {
	int count = lstControl->getCount();
	for (int i = 0; i < count; i++) {
		Control *c = (Control*)this->lstControl->getItem(i);
		c->jointed = !c->jointed;
	}
}
bool Control::into(Point point) {
	real X = point.x;
	real Y = point.y;
	Rect R = *this;
	R.correct();
	if (R.getX1() <= X && R.getY1() <= Y && R.getX2() >= X && R.getY2() >= Y) return true;
	return false;
}
bool Control::into(real X, real Y) {
	Rect R = *this;
	R.correct();
	if (R.getX1() <= X && R.getY1() <= Y && R.getX2() >= X && R.getY2() >= Y) return true;
	return false;
}
bool Control::into(Rect rect) {
	Rect R1 = rect;
	R1.correct();
	Rect R2 = *this;
	R2.correct();
	if (R1.getX1() <= R2.getX1() && R1.getY1() <= R2.getY1() &&
	R1.getX2() >= R2.getX2() && R1.getY2() >= R2.getY2()) return true;
	return false;
}

void Control::clone(Control *&control)
{
/*
	String s = getClassName();
	ClassInfo *ci = application->mngClass->findClass(S);
	Control = (Control*)ci->OnCreate(owner);
	CMemory mem;
	this->Object_WriteTo(&mem);
	mem.setPos(0);
	Control->Object_ReadFrom(&mem);
*/
}
void Control::clone(Control *owner, Control *&control)
{
	/*
	String S = getClassName();
	ClassInfo *ci = application->mngClass->findClass(S);
	Control = (Control*)ci->OnCreate(owner);
	CMemory mem;
	this->Object_WriteTo(&mem);
	mem.setPos(0);
	Control->Object_ReadFrom(&mem);

	Control->lstPoint.clear();
	int count = this->lstPoint.getCount();
	for (int i = 0; i < count; i++) {
		Point *p = (Point*)lstPoint.getItem(i);
		Control->lstPoint.add(p);
	}
	*/

//Control->Join(true);
//  Control->Assign(this);
}
void Control::assign(Control* control)
{
	if (control == NULL) return;
	anchors = control->anchors;
	visible = control->visible;
	color = control->color;
	penStyle = control->penStyle;
	penWidth = control->penWidth;
	brushStyle = control->brushStyle;

	index = control->index;
	set(*control);
	int count = control->JControls_GetCount();
	for (int i = 0; i < count; i++)
	{
		Control *ci = control->JControls_GetItem(i);
		Control *c;
		ci->clone(this, c);
	}
	count = control->UControls_GetCount();
	for (int i = 0; i < count; i++)
	{
		Control *ci = control->UControls_GetItem(i);
		Control *c;
		ci->clone(this, c);
	}

	this->lstPoint.clear();
	count = control->lstPoint.getCount();
	for (int i = 0; i < count; i++) {
		Point *p = (Point*)control->lstPoint.getItem(i);
		this->lstPoint.add(p);
	}
}
Rect Control::rect1AndRect2(Rect rect1, Rect rect2) {
	real r1x1 = rect1.getX1();
	real r1y1 = rect1.getY1();
	real r1x2 = rect1.getX2();
	real r1y2 = rect1.getY2();

	real r2x1 = rect2.getX1();
	real r2y1 = rect2.getY1();
	real r2x2 = rect2.getX2();
	real r2y2 = rect2.getY2();

	real x1 = r1x1;
	real y1 = r1y1;
	real x2 = r1x2;
	real y2 = r1y2;

	if (r1x1 < r2x1) x1 = r2x1;
	if (r1y1 < r2y1) y1 = r2y1;
	if (r1x2 > r2x2) x2 = r2x2;
	if (r1y2 > r2y2) y2 = r2y2;

	return Rect(x1, y1, x2, y2, false);

/*
	if (rect1.getX1() < rect2.getX1()) rect1.setX1(rect2.getX1());
	if (rect1.getY1() < rect2.getY1()) rect1.setY1(rect2.getY1());
	if (rect1.getX2() > rect2.getX2()) rect1.setX2(rect2.getX2());
	if (rect1.getY2() > rect2.getY2()) rect1.setY2(rect2.getY2());
*/
}
void Control::keyPress(String &key)
{
  if (onKeyPress) onKeyPress(this, key);
}
void Control::keyDown(int &key, ShiftKeys shift)
{
  if (onKeyDown) onKeyDown(this, key, shift);
}
void Control::keyUp(int &key, ShiftKeys shift)
{
  if (onKeyUp) onKeyUp(this, key, shift);
}
/*
		String s = c->getObjectName();
		if (s == "testobj") {
			int a = 1;
		}
		String s1;
		if (owner != NULL) {
			s1 = owner->getObjectName();
		}
*/
Control* Control::searchOuter(Point &point) {
	int count = UControls_GetCount();
	for (int i = count - 1; i >= 0; i--) {
		Control *c = UControls_GetItem(i);
		if (!c->visible) continue;
		Point m = point;
		m.decPos(c->pos);
		if (c->into(point)) {
			point = m;
			Control *c2 = c->searchOuter(m);
			if (c2 != NULL) {
				point = m;
				return c2;
			}
			else return c;
		}
	}
	return NULL;
}

void Control::mouseDown(MouseButton button, ShiftKeys shift, Point point) {
	isInto = true;
	isDown = true;
	String s = getObjectName();

	if (onMouseDown) 
		onMouseDown(this, button, shift, point);
	else {
		int count = UControls_GetCount();
		for (int i = 0; i < count; i++)	{
			Control *c = UControls_GetItem(i);
			c->mouseDown(button, shift, point);
		}
	}
}
void Control::mouseMove(ShiftKeys shift, Point point) {
	isInto = point.x >= 0 && point.y >= 0 && point.x <= getWidth() && point.y <= getHeight();
	if (onMouseMove) onMouseMove(this, shift, point);

	if (this->hint == "123")
		int a = 1;

	canvas->hint = this->hint;
	canvas->hintPos = this->getAbsolutePos();
	canvas->hintPos.incPos(Point(this->size.w / 2, 30));

	repaint(); ///!!! Внимание! Возможно здесь ошибка!
}
void Control::mouseUp(MouseButton button, ShiftKeys shift, Point point) {
	isDown = false;
	if (onMouseUp) onMouseUp(this, button, shift, point);
	if (point.x >= 0 && point.y >= 0 && point.x <= getWidth() && point.y <= getHeight())
		click();
	isInto = false;
}
void Control::click() {
	if (onClick) 
		onClick(this);
}
void Control::setBounds(real x, real y, real w, real h) {
	Rect oldRect = *this;
	Rect rect(x, y, w, h, true);
	Rect::setBounds(x, y, w, h);
	if (stretch) setPoints(rect, oldRect);
	setChilds(rect, oldRect);
}
void Control::setPoints(Rect rect, Rect oldRect) {
	int count = lstPoint.getCount();
	if (count == 0) return;
	real dX = rect.getWidth() / oldRect.getWidth();
	real dY = rect.getHeight() / oldRect.getHeight();
	for (int i = 0; i < count; i++) {
		Point *point = (Point*)lstPoint.getItem(i);
		point->x *= dX;
		point->y *= dY;
	}
}
void Control::setChilds(Rect rect, Rect oldRect) {
	int count = JControls_GetCount();
	for (int i = 0; i < count; i++)	{
		Control *c = JControls_GetItem(i);
		setByAnchors(oldRect, c);
	}
	count = UControls_GetCount();
	for (int i = 0; i < count; i++)	{
		Control *c = UControls_GetItem(i);
		setByAnchors(oldRect, c);
	}
}
void Control::setByAlign(Rect rect, Control *control) {
}
void Control::setByAnchors(Rect oldRect, Control *control) {
	Size scale(getWidth() / oldRect.getWidth(), getHeight() / oldRect.getHeight());
	Point crt((getCenter().x - oldRect.getCenter().x), (getCenter().y - oldRect.getCenter().y));
	Size size(getWidth() - oldRect.getWidth(), getHeight() - oldRect.getHeight());

	if (scale.w < 0) scale.w = -scale.w;
	if (scale.h < 0) scale.h = -scale.h;

	Rect myr = *control;

	Point MyOfs1(myr.getX1(), myr.getY1());
	real W2 = oldRect.getWidth();
	if (W2 < 0) W2 = - W2;
	real H2 = oldRect.getHeight();
	if (H2 < 0) H2 = - H2;
	Point MyOfs2(W2 - myr.getX2(), H2 - myr.getY2());
	if (MyOfs2.x < 0) MyOfs2.x = -MyOfs2.x;
	if (MyOfs2.y < 0) MyOfs2.y = -MyOfs2.y;

	real W = getWidth();
	if (W < 0) W = - W;
	real H = getHeight();
	if (H < 0) H = - H;

	switch (control->anchors.x1)
	{
	case 0:
		myr.setX1(myr.getX1() + crt.x);
		break;
	case 1:
		break;
	case 2:
		myr.setX1(myr.getX1() + size.w);
		break;
	case 3:
		myr.setX1(myr.getX1() * scale.w);
		break;
	case 4:
		myr.setX1(myr.getX1() * scale.w);
		break;
	}
	switch (control->anchors.y1)
	{
	case 0:
		myr.setY1(myr.getY1() + crt.y);
		break;
	case 1:
		break;
	case 2:
		myr.setY1(myr.getY1() + size.h);
		break;
	case 3:
		myr.setY1(myr.getY1() * scale.h);
		break;
	case 4:
		myr.setY1(myr.getY1() * scale.h);
		break;
	}

	switch (control->anchors.x2)
	{
	case 0:
		myr.setX2(myr.getX2() + crt.x);
		break;
	case 1:
		break;
	case 2:
		myr.setX2(myr.getX2() + size.w);
		break;
	case 3:
		myr.setX2(myr.getX2() * scale.w);
		break;
	case 4:
		myr.setX2(W - MyOfs2.x * scale.w);
		//    myr.getX2() *= scale.w;
		////    myr.getX2() = (R.getX2() - M2.x) * scale.w;
		break;
	}

	switch (control->anchors.y2)
	{
	case 0:
		myr.setY2(myr.getY2() + crt.y);
		break;
	case 1:
		break;
	case 2:
		myr.setY2(myr.getY2() + size.h);
		break;
	case 3:
		myr.setY2(myr.getY2() * scale.h);
		break;
	case 4:
		myr.setY2(H - MyOfs2.y * scale.h);
		break;
	}
	control->setRect(myr.getX1(), myr.getY1(), myr.getX2(), myr.getY2());
}


//--------------------------------------------------------------------------------------------------
//----------          Класс Line          ----------------------------------------------------------
//--------------------------------------------------------------------------------------------------
Line::Line(Control *owner) : Control(owner) {
}
String Line::getClassName() {
	return "Line";
}
Object* Line::createObject(List *params) {
	if (params == NULL) return NULL;
	if (params->getCount() != 1) return NULL;
	Control *owner = (Control*)params->getItem(0);
	if (owner == NULL) return NULL;
	return new Line(owner);
}

void Line::paint(Rect rect) {
	canvas->color = color;
	canvas->penWidth = penWidth;
	canvas->penStyle = penStyle;
	//canvas->brushStyle = brushStyle;
	canvas->line(Rect(Point(0, 0), Size(size.w - 1, size.h - 1)));
}

//--------------------------------------------------------------------------------------------------
//----------          Класс Rectangle          -----------------------------------------------------
//--------------------------------------------------------------------------------------------------
Rectangle::Rectangle(Control *owner) : Control(owner) {
}
String Rectangle::getClassName() {
	return "Rectangle";
}
Object* Rectangle::createObject(List *params) {
	if (params == NULL) return NULL;
	if (params->getCount() != 1) return NULL;
	Control *owner = (Control*)params->getItem(0);
	if (owner == NULL) return NULL;
	return new Rectangle(owner);
}

void Rectangle::paint(Rect rect) {
	canvas->color = color;
	canvas->penWidth = penWidth;
	canvas->penStyle = penStyle;
	canvas->brushStyle = brushStyle;
	canvas->rectangle(Rect(Point(0, 0), size));
}

//--------------------------------------------------------------------------------------------------
//----------          Класс Ellipse          -------------------------------------------------------
//--------------------------------------------------------------------------------------------------

Ellipse::Ellipse(Control *owner) : Control(owner) {
}
String Ellipse::getClassName() {
	return "Ellipse";
}
void Ellipse::paint(Rect rect) {
	if (!visible) return;
	canvas->color = color;
	canvas->ellipse(*this);
//	Control::paint(rect);
}


//---------------------------------------------------------------------------
//----------   Polyline   --------------------------------------------------
//---------------------------------------------------------------------------
Polyline::Polyline(Control *owner) : Control(owner) {
}
String Polyline::getClassName() {
	return "Polyline";
}
void Polyline::paint(Rect rect) {
	if (!visible) return;
	canvas->setColor(color);
	canvas->setOffset(Point(0, 0));
	canvas->polyline(getAbsoluteRect(), &lstPoint);
	Control::paint(rect);
}
void Polyline::setScale(real scaleX, real scaleY) {
}
void Polyline::normalize() {
}
void Polyline::maximize() {
}
void Polyline::pointByAngle(int pointCount, Point middle) {
}
void Polyline::updateRect() {
	int count = this->lstPoint.getCount();
	if (count > 0) {
		Point *p = (Point*)lstPoint.getItem(0);
		Point min, max;
		min = *p;
		max = *p;
		for (int i = 1; i < count; i++) {
			p = (Point*)lstPoint.getItem(i);
			if (min.x > p->x) min.x = p->x;
			if (min.y > p->y) min.y = p->y;
			if (max.x < p->x) max.x = p->x;
			if (max.y < p->y) max.y = p->y;
		}
		/*
		if (min.x > minX) min.x = minX;
		if (min.y > minY) min.y = minY;
		if (max.x < maxX) max.x = maxX;
		if (max.y < maxY) max.y = maxY;
		*/
		for (int i = 0; i < count; i++) {
			p = (Point*)lstPoint.getItem(i);
			p->decPos(min);
		}
		min.x = floor(min.x + pos.x);
		min.y = floor(min.y + pos.y);
		max.x = ceil(max.x + pos.x);
		max.y = ceil(max.y + pos.y);
		this->stretch = false;
		this->set(min, max);
		this->stretch = true;
	}
}
void Polyline::setStyle(int style) {
}

//---------------------------------------------------------------------------
//----------   Polygon   ----------------------------------------------------
//---------------------------------------------------------------------------
Polygon::Polygon(Control *owner) : Polyline(owner) {
}
String Polygon::getClassName() {
	return "Polygon";
}
void Polygon::paint(Rect rect) {
	if (!visible) return;
	canvas->color = color;
	canvas->penWidth = penWidth;
	canvas->penStyle = penStyle;
	canvas->brushStyle = brushStyle;

	canvas->polygon(Rect(0, 0, rect.getW(), rect.getH(), true) , &lstPoint);
	Polyline::paint(rect);
}
void Polygon::dePointCount(int value)
{
  bool Flag = false;
  while (true) {
    int count = lstPoint.getCount();
    if (count <= value) return;
    int MinIndex = 0;
    for (int i = count - 1; i >= 0; i -= 2) {
      if (count <= value) return;
      lstPoint.remove(i);
      count--;
    }
  }
}
Point Polygon::calcMidPoint()
{
  Point mid(0, 0);
  int count = lstPoint.getCount();
  if (count < 1) return mid;
  for (int i = 0; i < count; i++) {
    Point *M = (Point*)lstPoint.getItem(i);
    mid.x += M->x;
    mid.y += M->y;
  }
  mid.x /= count;
  mid.y /= count;
  return mid;
}
Point* Polygon::getPrevPoint(Point *M)
{
  int count = lstPoint.getCount();
  if (count == 0) return NULL;
  int Index = lstPoint.indexOf(M);
  Index--;
  if (Index < 0) Index = count - 1;
  Point *m = (Point*)lstPoint.getItem(Index);
  return m;
}
Point* Polygon::getNextPoint(Point *M)
{
  int count = lstPoint.getCount();
  if (count == 0) return NULL;
  int Index = lstPoint.indexOf(M);
  Index++;
  if (Index >= count) Index = 0;
  Point *m = (Point*)lstPoint.getItem(Index);
  return m;
}
bool Polygon::lineCross(Point *A, Point *B, Point *C, Point *D, Point &Cross)
{
  real x1, y1, x2, y2, x1s, y1s, x2s, y2s, x0, y0;
  x1 = A->x;
  y1 = A->y;
  x2 = B->x;
  y2 = B->y;
  x1s = C->x;
  y1s = C->y;
  x2s = D->x;
  y2s = D->y;

  if (x1 == x2) {
    x0 = x1;
    y0 = y2s - (x1s * (y2s - y1s)) / (x2s - x1s);
  }
  else if (y1 == y2) {
    y0 = y1;
    if (x1s == x2s) x0 = x1s;
    else {
      if (y1s == y2s) x0 = (x1s - x2s) / 2;
      else
      {
        real ks = (y2s - y1s) / (x2s - x1s);
        try {
          x0 = x2s - (y2s - y1) / ks;
        } catch(...) {
          x0 = x2s - (y2s - y1) / ks;
        }
      }  
    }
  }
  else {
    real k = (y2 - y1) / (x2 - x1);
    if (k == 0)
      return false;

    if (x2s - x1s == 0)
      return false;

    real ks = (y2s - y1s) / (x2s - x1s);
    real m = y2s - ks * x2s;
    real n = x2 - y2 / k;

    y0 = (m + ks * n) / (1 - ks / k);
    x0 = n + y0 / k;
  }
  Cross.x = x0;
  Cross.y = y0;

  if (x1 > x2)
    swap(x1, x2);
  if (y1 > y2)
    swap(y1, y2);
  if (x1s > x2s)
    swap(x1s, x2s);
  if (y1s > y2s)
    swap(y1s, y2s);

  if (x1 <= x0 && y1 <= y0 && x0 <= x2 && y0 <= y2 &&
      x1s <= x0 && y1s <= y0 && x0 <= x2s && y0 <= y2s) return true;
  return false;
}
real Polygon::calcLengthM1M2(Point point1, Point point2) {
	real len = sqrt((point1.x - point1.y) * (point1.x - point1.y) + (point2.x - point2.y) * (point2.x - point2.y));
	return len;
}


//---------------------------------------------------------------------------
//----------   Splinegon   -------------------------------------------------
//---------------------------------------------------------------------------
Splinegon::Splinegon(Control *owner) : Polygon(owner) {
	rounding = 3;
	minX = minY = maxX = maxY = 0;
}
String Splinegon::getClassName() {
	return "Splinegon";
}
void Splinegon::paint(Rect rect) {
	if (!visible) return;
	canvas->color = color;
	canvas->penWidth = penWidth;
	canvas->penStyle = penStyle;
	canvas->brushStyle = brushStyle;

	if (rounding > 0) {
		lstRounding.clear();
		int count = lstPoint.getCount();
		for (int i = 0; i < count; i++) {
			Point *p1 = (Point*)lstPoint.getItem(i);
			Point *p2 = new Point(p1->x, p1->y);
			lstRounding.add(p2);
		}
		round(&lstRounding, rounding);
		canvas->polygon(Rect(0, 0, rect.getW(), rect.getH(), true), &lstRounding);
	}
	else {
		canvas->polygon(Rect(0, 0, rect.getW(), rect.getH(), true), &lstPoint);
		lstRounding.assign(&lstPoint);
	}
	//  canvas->Brush_Polygon(getAbsoluteRect(), &lstPoint);
	//  canvas->Pen_Bezier(getAbsoluteRect(), &lstPoint);
	//Control::paint(rect);
}
void Splinegon::calcRounding() {
	if (rounding > 0) {
		lstRounding.clear();
		int count = lstPoint.getCount();
		for (int i = 0; i < count; i++) {
			Point *p1 = (Point*)lstPoint.getItem(i);
			Point *p2 = new Point(p1->x, p1->y);
			lstRounding.add(p2);
		}
		round(&lstRounding, rounding);
	}
}
void Splinegon::round(List *lstPoint) {
	int count = lstPoint->getCount();
	if (count < 3) return;
	
	int i = 0; 
	while (i < count) {
		if (i == 0) {
			int i0 = i;
			int i1 = i + 1;
			if (i1 >= count) i1 = i1 - count;
			int i2 = i + 2;
			if (i2 >= count) i2 = i2 - count;

			Point *m0 = (Point*)lstPoint->getItem(i0);
			Point *m1 = (Point*)lstPoint->getItem(i1);
			Point *m2 = (Point*)lstPoint->getItem(i2);

			real x01 = (m0->x + m1->x) / 2;
			real y01 = (m0->y + m1->y) / 2;
			Point *m01 = new Point(x01, y01);
			lstPoint->insert(i1, m01);

			real x02 = (m1->x + m2->x) / 2;
			real y02 = (m1->y + m2->y) / 2;
			Point *m12 = new Point(x02, y02);
			int i3 = i + 3;
			if (i3 >= count) i3 = i3 - count;
			lstPoint->insert(i3, m12);

			real x = (m01->x + m1->x + m12->x) / 3;
			real y = (m01->y + m1->y + m12->y) / 3;
			m1->set(x, y);

			i += 3;
		}
		else if (i + 1 == count) {
			/*
			String S = "";
			for (int j = 0; j < count; j++) {
				Point *m = (Point*)lstPoint.getItem(j);
				int x = m->x;
				int y = m->y;
				S = S + (String)x + "," + (String)y + "  ";
			}
			*/
			int i0 = i;
			int i1 = i + 1;
			if (i1 >= count) i1 = i1 - count;
			int i2 = i + 2;
			if (i2 >= count) i2 = i2 - count;

			Point *m0 = (Point*)lstPoint->getItem(i0);
			Point *m1 = (Point*)lstPoint->getItem(i1);
			Point *m2 = (Point*)lstPoint->getItem(i2);

			real x = (m0->x + m1->x + m2->x) / 3;
			real y = (m0->y + m1->y + m2->y) / 3;
			m1->set(x, y);
			
			break;
		}
		else {
			int i0 = i;
			int i1 = i + 1;
			if (i1 >= count) i1 = i1 - count;
			int i2 = i + 2;
			if (i2 >= count) i2 = i2 - count;

			Point *m0 = (Point*)lstPoint->getItem(i0);
			Point *m1 = (Point*)lstPoint->getItem(i1);
			Point *m2 = (Point*)lstPoint->getItem(i2);

			real x02 = (m1->x + m2->x) / 2;
			real y02 = (m1->y + m2->y) / 2;
			Point *m12 = new Point(x02, y02);
			if (i2 == 0) lstPoint->add(m12);
			else lstPoint->insert(i2, m12);

			real x = (m0->x + m1->x + m12->x) / 3;
			real y = (m0->y + m1->y + m12->y) / 3;
			m1->set(x, y);

			i += 2;
			//break;
		}
		count = lstPoint->getCount();
	}
}
void Splinegon::round2(List *lstPoint) {
	int count = lstPoint->getCount();
	if (count < 3) return;
	
	int i = 0; 
	while (i < count) {
		int i1 = i + 0, i2 = i + 1;
		if (i2 >= count) i2 = 0;
		Point *m1 = (Point*)lstPoint->getItem(i1);
		Point *m2 = (Point*)lstPoint->getItem(i2);
		real x12 = (m1->x + m2->x) / 2;
		real y12 = (m1->y + m2->y) / 2;
		Point *m12 = new Point(x12, y12);

		lstPoint->insert(i2, m12);

		i += 2;
		count = lstPoint->getCount();
	}

	count = lstPoint->getCount();	
	for (int i = 0; i < count; i += 2) {
		int i1 = i - 1, i2 = i + 1;
		if (i1 < 0)  i1 += count;
		if (i2 >= count) i2 -= count;

		int i0 = i - 3;
		if (i0 < 0) i0 = i0 + count;
		int i3 = i + 3;
		if (i3 >= count) i3 -= count;

		int iCur = i;

		Point *m0 = (Point*)lstPoint->getItem(i0);
		Point *m1 = (Point*)lstPoint->getItem(i1);
		Point *m2 = (Point*)lstPoint->getItem(i2);
		Point *m3 = (Point*)lstPoint->getItem(i3);

		Point *m12 = (Point*)lstPoint->getItem(iCur);

		if (i == 0) {
			minX = maxX = m1->x;
			minY = maxY = m1->y;
		}

		real x12 = (m1->x + m2->x) / 2;
		real y12 = (m1->y + m2->y) / 2;
		
		real x01 = (m0->x - m1->x) * 0.07;
		real x32 = (m3->x - m2->x) * 0.07;
		real y01 = (m0->y - m1->y) * 0.07;
		real y32 = (m3->y - m2->y) * 0.07;
		
/*
		real x012 = m0->x - x12;
		real x123 = x12 - m3->x;
		real y012 = m0->y - y12;
		real y123 = y12 - m3->y;

		x12 -= (x012 + x123) * 0.2;
		y12 -= (x012 + x123) * 0.2;
*/


		x12 += - x01 - x32;
		y12 += - y01 - y32; 
		m12->set(x12, y12);

		if (minX > x12) minX = x12;
		if (minY > y12) minY = y12;
		if (maxX < x12) maxX = x12;
		if (minY < y12) minY = y12;


		//i += 2;
		//count = lstPoint->getCount();
	}
}
void Splinegon::round3(List *lstPoint) {
	int count = lstPoint->getCount();
	if (count < 3) return;
	
	int i = 0, iSave = 0; 
	while (i < count) {
		int i1 = i + 0, i2 = i + 1;

		if (i2 >= count) {
			i2 = 0;
			iSave++;
		}
		Point *m1 = (Point*)lstPoint->getItem(i1);
		Point *m2 = (Point*)lstPoint->getItem(i2);
		real x12 = (m1->x + m2->x) / 2;
		real y12 = (m1->y + m2->y) / 2;
		Point *m12 = new Point(x12, y12);

		if (iSave > 0) lstPoint->add(m12);
		else
			lstPoint->insert(i2, m12);

		i += 2;
		count = lstPoint->getCount();
	}
//	showMessage(iSave);
//return;
	count = lstPoint->getCount();
	for (int i = 0; i < count; i += 2) {
		int i1 = i, i2 = i + 2;
		if (i1 < 0)  i1 += count;
		if (i2 >= count) i2 -= count;

		int i0 = i - 2;
		if (i0 < 0) i0 = i0 + count;
		int i3 = i + 4;
		if (i3 >= count) i3 -= count;

		int iCur = i + 1;
		if (iCur >= count) iCur -= count;

		Point m0 = *(Point*)lstPoint->getItem(i0);
		Point m1 = *(Point*)lstPoint->getItem(i1);
		Point m2 = *(Point*)lstPoint->getItem(i2);
		Point m3 = *(Point*)lstPoint->getItem(i3);
		Point *m12 = (Point*)lstPoint->getItem(iCur);
		
		Point c;
		if (!calcCircleCenter(m0, m1, m2, c)) continue;

		real r = sqrt((c.x - m0.x) * (c.x - m0.x) + (c.y - m0.y) * (c.y - m0.y));
		real s = sqrt((c.x - m12->x) * (c.x - m12->x) + (c.y - m12->y) * (c.y - m12->y));
		Point p1(c.x + (m12->x - c.x) * r / s, c.y + (m12->y - c.y) * r / s), p2;

		if (calcCircleCenter(m1, m2, m3, c)) {
			r = sqrt((c.x - m1.x) * (c.x - m1.x) + (c.y - m1.y) * (c.y - m1.y));
			s = sqrt((c.x - m12->x) * (c.x - m12->x) + (c.y - m12->y) * (c.y - m12->y));
			p2.set(c.x + (m12->x - c.x) * r / s, c.y + (m12->y - c.y) * r / s);
			m12->set((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
		}
		else m12->set(p1.x, p1.y);
	}
}
bool Splinegon::calcCircleCenter(Point p1, Point p2, Point p3, Point& center) {
	real x1 = p1.x;
	real y1 = p1.y;
	real x2 = p2.x;
	real y2 = p2.y;
	real x3 = p3.x;
	real y3 = p3.y;

	bool flag = false;
	for (int i = 0; i < 3; i++) {
		if (fabs(x2 - x1) > 0.000001 && fabs(x3 - x2) > 0.000001) {
			flag = true;
			break;
		}
		real swX = x1, swY = y1;
		x1 = x2; y1 = y2;
		x2 = x3; y2 = y3;
		x3 = swX; y3 = swY;
	}
	if (!flag) return false;

	real ma = (y2 - y1) / (x2 - x1);
	real mb = (y3 - y2) / (x3 - x2);
	if (fabs(mb - ma) < 0.000001) return false;

	real x = (ma * mb * (y1 - y3) + mb * (x1 + x2) - ma * (x2 + x3)) / (2 * (mb - ma));

	real y;
	if (fabs(ma) > 0.000001) y = -1 / ma * (x - (x1 + x2) / 2) + (y1 + y2) / 2;
	else y = -1 / mb * (x - (x2 + x3) / 2) + (y2 + y3) / 2;

	center.set(x, y);
	return true;
}
void Splinegon::round(List *lstPoint, int iteration) {
	for (int i = 0; i < iteration; i++) {
		round3(lstPoint);
	}
}


//---------------------------------------------------------------------------
//----------   Text   ------------------------------------------------------
//---------------------------------------------------------------------------
Text::Text(Control *owner) : Control(owner)
{
	PosShift = 0;
	isCenter = false;
	fontId = 0;
	str = "Hello, word!";
	color.set(0, 0, 0);
}
String Text::getClassName()
{
	return "Text";
}
Size Text::getTextSize()
{
	canvas->setFontId(fontId);
	return canvas->getTextSize(str);
}
Size Text::getCustomTextSize(String AText)
{
	return canvas->getTextSize(AText);
}
int Text::getFontId()
{
	return fontId;
}
void Text::setFontId(int value)
{
	fontId = value;
}
String Text::getFontName()
{
#ifdef OS_WINDOWS
	///Font *f = application->mngFont->getFont(fontId);
	///return f->getObjectName();
#endif
#ifdef OS_LINUX
	///return "";
#endif
	return "";
}
void Text::setFontName(String value)
{
#ifdef OS_WINDOWS
  ///fontId = application->mngFont->getId(value);
#endif
}
void Text::createFont(int Width, int Height, bool W, bool I, bool U, bool S, bool D3, String fontName)
{
  Font *fnt = new Font;
  String name = fontName + Width + Height;
  if (W) name += "w";
  if (I) name += "i";
  if (U) name += "u";
  if (S) name += "s";
  if (D3) name += "3d";
  fnt->set(Width, Height, W, I, U, S, D3, fontName, name);
  fontId = canvas->registerFont(fnt);
}
void Text::paint(Rect rect)
{
	//canvas->setOffset(getAbsoluteOffset());
	canvas->setColor(color);
	canvas->setFontId(fontId);
	Rect *R = this;
	if (isCenter) canvas->text(Rect(0, 0, R->getW(), R->getH()), str);
	else canvas->text(Point(0, 0), str);
}
void Text::doNormal()
{
	Size sz = getTextSize();
	setX2(getX1() + sz.w);
	setY2(getY1() + sz.h);
}
//---------------------------------------------------------------------------
//----------   Image   -------------------------------------------------------
//---------------------------------------------------------------------------
Image::Image(Control *owner) : Control(owner) {
	fileName = "";
	isCenter = false;
	bitmap = NULL;
	if (canvas != NULL) bitmap = canvas->createBitmap();
}
String Image::getClassName() {
	return "Image";
}

bool Image::loadFromFile(String AFileName) {
	fileName = AFileName;
	return bitmap->loadFromFile(fileName);
}
void Image::paint(Rect rect) {
	if (!visible) return;
	if (canvas == NULL) return;
	Rect R = getRect();
	R.correct();
	Point point = getAbsoluteOffset();
	//canvas->setOffset(point);
	if (!isCenter) canvas->image(R, bitmap);
	else canvas->imageCenter(R, bitmap);
}

}
