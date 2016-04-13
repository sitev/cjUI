#include "cj.h"
#include "cjUI.h"

namespace cj {

//---------------------------------------------------------------------------
//----- Font ------------------------------------------------------------
//---------------------------------------------------------------------------
Font::Font()
{
}
void Font::set(int width, int height, bool w, bool i, bool u, bool s, bool d3, String fontName, String name) {
  this->width = width;
  this->height = height;
  this->w = w;
  this->i = i;
  this->u = u;
  this->s = s;
  this->d3 = d3;
  this->fontName = fontName;
  setObjectName(name);
}
bool Font::compare(Font *fnt)
{
//  if (ID != fnt->ID) return false;
  if (width != fnt->width) return false;
  if (height != fnt->height) return false;
  if (w != fnt->w) return false;
  if (i != fnt->i) return false;
  if (u != fnt->u) return false;
  if (s != fnt->s) return false;
  if (d3 != fnt->d3) return false;
  if (fontName != fnt->fontName) return false;
  return true;
}
//---------------------------------------------------------------------------
//----- COpenGLFont ------------------------------------------------------
//---------------------------------------------------------------------------
/*
void COpenGLFont::CreateFont(int W, int H, CSet *Params, String fontName)
{
  int count = Params->getCount();
  if (count != 4) return;
  bool Weight = *Params->getItem(0);
  bool Italic = *Params->getItem(1);
  bool Underline = *Params->getItem(2);
  bool StrikeOut = *Params->getItem(3);

//	GLYPHMETRICSFLOAT agmf[256];
	LOGFONT logfont;
	logfont.lfHeight = H.GetInt();
	logfont.lfWidth = W.GetInt();
	logfont.lfEscapement = 0;
	logfont.lfOrientation = 0;
  if (Weight)	logfont.lfWeight = 700;
  else logfont.lfWeight = 400;
	logfont.lfItalic = Italic;
	logfont.lfUnderline = Underline;
	logfont.lfStrikeOut = StrikeOut;
	logfont.lfCharSet = ANSI_CHARSET;
	logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	logfont.lfQuality = DEFAULT_QUALITY;
	logfont.lfPitchAndFamily = DEFAULT_PITCH;
	strcpy(logfont.lfFaceName, fontName.GetChars());

	// Create the font and display list
  hFont = CreateFontIndirect(&logfont);
//  HDC hdc =
//  SelectObject (hdc, GetStockObject (SYSTEM_FONT));
//	SelectObject (hdc, hFont);
//	wglUseFontOutlines(hdc, 0, 255, 1000, 0.001f, 1.0f, WGL_FONT_POLYGONS, agmf);
//	SelectObject(control->View->hdc, hFont);
//  wglUseFontBitmaps (control->View->hdc, 0, 255, 1000);
//  Form->font->Handle = hFont;
//	DeleteObject(hFont);
}
*/
/*
Size COpenGLFont::getTextSize(Canvas *Canvas, String S)
{
  SIZE SZ;
  GetTextExtentPoint32(((COpenGL*)Canvas)->hdc, S.GetChars(),
    S.Length().GetInt(), &SZ);
  return Size(SZ.cx, SZ.cy);
}
*/
//---------------------------------------------------------------------------
//----- FontManager -----------------------------------------------------
//---------------------------------------------------------------------------
FontManager::FontManager() {
}
Font* FontManager::getFont(String value) {
	int count = lstFont.getCount();
	for (int i = 0; i < count; i++) {
		Font *f = (Font*)lstFont.getItem(i);
		if (f->getObjectName() == value) return f;
	}
	return NULL;
}
Font* FontManager::getFont(int id) {
	int count = lstFont.getCount();
	if (id < 0 || id >= count) return NULL;
	return (Font*)lstFont.getItem(id);
}
int FontManager::getId(Font* value) {
	if (value == NULL) return -1;
	int count = lstFont.getCount();
	for (int i = 0; i < count; i++) {
		Font *f = getFont(i);
		if (f == value) return i;
	}
	return -1;
}
int FontManager::getId(String value) {
	if (value == "") return -1;
	int count = lstFont.getCount();
	for (int i = 0; i < count; i++) {
		Font *f = getFont(i);
		if (f->getObjectName() == value) return i;
	}
	return -1;
}

}