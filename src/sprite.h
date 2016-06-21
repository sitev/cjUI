#pragma once

#include "cjUI.h"

namespace cj {

#ifdef CONTROL_CLASS
#ifdef TEXTURE_CLASS

	class Sprite : public Control {
	public:
		Sprite(Control *owner);
		virtual void paint(Rect rect);

		virtual void setTexture(Texture &tx) = 0;
		virtual void setTextureRect(Rect rect) = 0;
		virtual void setPosition(int x, int y) = 0;
	};

#endif
#endif

}