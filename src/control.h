#pragma once

#include "cjUI.h"
#include "closure.h"

namespace cj {

const int maxNormPntCnt = 36;

enum MouseButton {mbtLeft, mbtMiddle, mbtRight};

class ShiftKeys : public Object
{
private:
public:
  bool shift, alt, ctrl;
  ShiftKeys();
};

enum Cursor {crDefault = 0, crNone = -1, crArrow = -2, crCross = -3, crIBeam = -4, 
  crSizeNESW = -6, crSizeNS	= -7, crSizeNWSE = -8, crSizeWE = -9};
enum Align {alNone, alLeft, alTop, alRight, alBottom, alClient};


#ifdef OS_WINDOWS

enum PenStyle {psSolid = PS_SOLID, psDash = PS_DASH, psDot = PS_DOT, psDashDot = PS_DASHDOT,
psDashDotDot = PS_DASHDOTDOT, psNull = PS_NULL};

enum BrushStyle {bsSolid = -1,	bsHorizontal = HS_HORIZONTAL, bsVertical = HS_VERTICAL, bsFDiagonal = HS_FDIAGONAL, 
	bsBDiagonal = HS_BDIAGONAL, bsCross = HS_CROSS, bsDiagCross = HS_DIAGCROSS, bsNull = HS_DIAGCROSS + 1};

#endif

#ifdef OS_LINUX

enum PenStyle {psSolid = 1, psDash = 2, psDot = 3, psDashDot = 4,
psDashDotDot = 5, psNull = 0};

enum BrushStyle {bsSolid = -1,	bsHorizontal = 1, bsVertical = 2, bsFDiagonal = 3,
	bsBDiagonal = 4, bsCross = 5, bsDiagCross = 6, bsNull = 0};

#endif


typedef Closure<void(Object *sender)> NotifyEvent;

#define nullEvent getEvent()
typedef Object* (*CreateFunc)(List *params);

typedef Closure<void(Object *sender)> ClickEvent;
typedef Closure<void(Object* sender, MouseButton List, ShiftKeys shift, Point point)> MouseEvent;
typedef Closure<void(Object* sender, ShiftKeys shift, Point point)> MouseMoveEvent;
typedef Closure<void(Object* sender, int delta)> MouseWheelEvent;
typedef Closure<void(Object* sender, String &key)> KeyPressEvent;
typedef Closure<void(Object* sender, int &key, ShiftKeys shift)> KeyEvent;
typedef Closure<void(Object *sender, Rect rect)> PaintEvent;
typedef Closure<void(Object *sender, Size size)> ResizeEvent;


/*
class Align : public Object
{
	AlignType Value;
public:
	Align();
	virtual AlignType get();
	virtual void set(AlignType value);
};
*/
class Anchors : public Object
{
public:
	int x1, y1, x2, y2;
/*
0 - �����
1 - ���� ��� �����
2 - ������ ��� ����
3 - ���� ��� ����� � ���������
4 - ������ ��� ���� � ���������
*/
	Anchors();
	Anchors(int x1, int y1, int x2, int y2);
	Anchors operator=(Anchors value);
	virtual void set(int x1, int y1, int x2, int y2);
};

class Track;
class Canvas;

class Control : public Rect {
protected:
	bool isInto, isDown, isCanvas;
	Rect saveRect;
public:
	Control *owner;
	Canvas *canvas;

    MouseEvent onMouseDown; //������� ������� ������ ����
    MouseMoveEvent onMouseMove; //������� ����������� ����
    MouseEvent onMouseUp; //������� ���������� ������ ����
	MouseWheelEvent onMouseWheel; //������� �������� �������
    KeyPressEvent onKeyPress; //������� ������� �������
    KeyEvent onKeyDown; //������� ������� ������� ����
    KeyEvent onKeyUp; //������� ���������� ������� �����
    PaintEvent onPaint; //������� ���������
    NotifyEvent onClose; //������� ����������
    ResizeEvent onResize; //������� ��������� �������
	ClickEvent onClick;

	bool visible, enabled;
	Color color;
	int penWidth;
	PenStyle penStyle; 
	BrushStyle brushStyle;
	List *lstControl, lstPoint;
	Control *client;
	Align align;
	Anchors anchors;
	bool jointed;
	int index;
	bool stretch;
	bool isScissor;
	String hint;

	Control(Control *owner);
	virtual ~Control();

	virtual String getClassName();

	virtual Control* getOwner();
	virtual void setOwner(Control *owner);
	virtual Canvas* getCanvas();
	virtual void setCanvas(Canvas *owner);

	virtual void recalc(Rect rect);
	virtual void paintControl(Rect rect);
	virtual void paintBegin(Rect &rect);
	virtual void paint(Rect rect);
	virtual void paintInner(Rect rect);
	virtual void paintOuter(Rect rect);
	virtual void paintTrackBegin(Rect &rect);
	virtual void paintTrack(Rect &rect);
	virtual void paintTrackEnd(Rect &rect);
	virtual void paintEnd(Rect rect);
	virtual void repaint();

	virtual void changeRect(real x1, real y1, real x2, real y2);

	virtual void releasePaintRect() {}


	virtual bool getVisible();
	virtual void setVisible(bool value);

	virtual void setColor(Color c);
	virtual void setColor(real r, real g, real b);
	virtual void setPenWidth(int value);
	virtual void setPenStyle(PenStyle value);
	virtual void setBrushStyle(BrushStyle value);

	

	virtual Point getAbsoluteOffset();
	virtual Point getAbsolutePos();
	virtual Rect getAbsoluteRect();

	virtual String getFontName();
	virtual void setFontName(String value);
	virtual Point getOffset();
//	virtual void setOffset(Point value);
	virtual void setScale(real scaleX, real scaleY) {}

	virtual int indexOf();

	virtual void joint(bool value);

	bool JControls_Exist();//�������� ���������� ��� ���
	int JControls_GetCount();//�������� ���������� ���������
	int JControls_GetControlsIndex(int index);
	int JControls_GetJControlsIndex(int ControlsIndex);
	void JControls_Add(Control* Item);//�������� �������
	void JControls_Insert(int index, Control* Item);//�������� �������
	Control* JControls_GetItem(int index);//�������� ������� �� �������
	void JControls_SetItem(int index, Control* Data);//���������� ����� ������� �� �������
	void JControls_Change(int Index1, int Index2);//�������� �������� �������
	void JControls_Delete(int index);//������� ������� �� ������
	void JControls_DeleteLight(int index);//������� ������� �� ������, �� ������� ��� � ������
	int JControls_IndexOf(Control* Item);//�������� ������ ��������
	int JControls_Remove(Control* Item);//������� ������� �� ������
	int JControls_RemoveLight(Control* Item);//������� ������� �� ������, �� ������� ��� � ������
	void JControls_Clear();//�������� ������ ���������
	void JControls_ClearLight();//�������� ������ ���������, ������� �� � ������

	bool UControls_Exist();//�������� ���������� ��� ���
	int UControls_GetCount();//�������� ���������� ���������
	int UControls_GetControlsIndex(int index);
	int UControls_GetUControlsIndex(int ControlsIndex);
	void UControls_Add(Control* Item);//�������� �������
	void UControls_Insert(int index, Control* Item);//�������� �������
	Control* UControls_GetItem(int index);//�������� ������� �� �������
	void UControls_SetItem(int index, Control* Data);//���������� ����� ������� �� �������
	void UControls_Change(int Index1, int Index2);//�������� �������� �������
	void UControls_Delete(int index);//������� ������� �� ������
	void UControls_DeleteLight(int index);//������� ������� �� ������, �� ������� ��� � ������
	int UControls_IndexOf(Control* Item);//�������� ������ ��������
	int UControls_Remove(Control* Item);//������� ������� �� ������
	int UControls_RemoveLight(Control* Item);//������� ������� �� ������, �� ������� ��� � ������
	void UControls_Clear();//�������� ������ ���������
	void UControls_ClearLight();//�������� ������ ���������, ������� �� � ������
	virtual void inverseJointAll();


	virtual void findTrack(Track *&t, Point &m, bool &stop) {}
	virtual void findControl(Control* &c, Point &m, bool &stop) {}
	virtual bool into(Point point);
	virtual bool into(real x, real y);
	virtual bool into(Rect rect);

	virtual void clone(Control *&control);
	virtual void clone(Control *owner, Control *&control);
	virtual void assign(Control* control);

	virtual Rect rect1AndRect2(Rect rect1, Rect rect2);

	virtual void keyPress(String &key);
	virtual void keyDown(int &key, ShiftKeys shift);
	virtual void keyUp(int &key, ShiftKeys shift);

	virtual Control* searchOuter(Point &point);
	virtual void mouseDown(MouseButton button, ShiftKeys shift, Point point);
	virtual void mouseMove(ShiftKeys shift, Point point);
	virtual void mouseUp(MouseButton button, ShiftKeys shift, Point point);
	virtual void click();

	virtual void setBounds(real x, real y, real w, real h);
private:
	virtual void setPoints(Rect rect, Rect oldRect);
	virtual void setChilds(Rect rect, Rect oldRect);
	virtual void setByAlign(Rect rect, Control *control);
	virtual void setByAnchors(Rect oldRect, Control *control);
};

class Line : public Control {
public:
	Line(Control *owner);
	virtual String getClassName();
	static Object* createObject(List *params);

	virtual void paint(Rect rect);
};

class Rectangle : public Control {
public:
	Rectangle(Control *owner);
	virtual String getClassName();
	static Object* createObject(List *params);

	virtual void paint(Rect rect);
};

class FillRectangle : public Rectangle {
};

class Ellipse : public Control {
public:
	Ellipse(Control *owner);
	virtual String getClassName();

	virtual void paint(Rect rect);
};

class RoundRect : public Control {
public:
	RoundRect(Control *owner);
	virtual String getClassName();

	virtual void paint(Rect rect);
};

class Polyline : public Control {
//�������-�������
public:
	Polyline(Control *owner);
	virtual String getClassName();
	virtual void paint(Rect rect);

	virtual void setScale(real scaleX, real scaleY);
	virtual void normalize();
	virtual void maximize();
	virtual void pointByAngle(int pointCount, Point middle);
	virtual void updateRect();

	virtual void setStyle(int style);
};
class Polygon : public Polyline {
//�������-�������
public:
	Polygon(Control *owner);
	virtual String getClassName();
	virtual void paint(Rect rect);

	virtual void dePointCount(int value);
	virtual Point calcMidPoint();
	virtual Point* getPrevPoint(Point *M);
	virtual Point* getNextPoint(Point *M);
	virtual bool lineCross(Point *A, Point *B, Point *C, Point *D, Point &Cross);
	virtual real calcLengthM1M2(Point p1, Point p2);
};
class Splinegon : public Polygon {
//�������-���������
private:
	real minX, minY, maxX, maxY;
public:
	int rounding;
	List lstRounding;

	Splinegon(Control *owner);
	virtual String getClassName();
	virtual void paint(Rect rect);

	virtual void round(List *lstPoint);
	virtual void round2(List *lstPoint);
	virtual void round3(List *lstPoint);
	virtual bool calcCircleCenter(Point p1, Point p2, Point p3, Point &center);
	virtual void calcRounding();

	virtual void round(List *lstPoint, int iteration);
//	virtual void updateRect();
};

class Text : public Control {
public:
	real PosShift;
	String str;
	int fontId;
	bool isCenter;
	Text(Control *owner);
	virtual String getClassName();

	virtual Size getTextSize();
	virtual Size getCustomTextSize(String value);
	virtual int getFontId();
	virtual void setFontId(int value);
	virtual String getFontName();
	virtual void setFontName(String value);
	virtual void createFont(int width, int height, bool w, bool i, bool u, bool s, bool d3, String fontName);
	virtual void paint(Rect rect);
	virtual void doNormal();
};
class Image : public Control {
public:
	Bitmap *bitmap;
	String fileName;
	bool isCenter;

	Image(Control *owner);
	virtual String getClassName();
	virtual bool loadFromFile(String fileName);
	virtual void paint(Rect rect);
};

}
