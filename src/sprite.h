#pragma once

#include "cjUI.h"

namespace cj {

#ifdef CONTROL_CLASS
#ifdef TEXTURE_CLASS

	class Sprite : public Control {
	protected:
		Texture *tx = NULL;
		SpriteClass *sc = NULL;
		SpriteState *ss = NULL;
		SpriteFrame *sf = NULL;

		bool animate = false;
		bool startAnimate = false;
		int interval = 1000;
		int saveTick;
	public:
		Sprite(Control *owner);
		virtual void paint(Rect rect);

		virtual void setTexture(Texture &tx) = 0;
		virtual void setTextureRect(Rect rect) = 0;
		virtual void setPosition(int x, int y) = 0;

		virtual void setClass(String value);
		virtual void setState(String value);
		virtual void setFrame(String value);

		virtual void setInterval(int msec);
		virtual void setAnimate(bool value);
	};

#endif
#endif
//тут был LEXX
}