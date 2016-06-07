#pragma once

#include "cjUI.h"

namespace cj {

#ifdef CONTROL_CLASS
//#ifndef SPRITE_CLASS
//#define SPRITE_CLASS

#include "cjUI.h"

	class Sprite : public Control {
	protected:
	public:
		Sprite(Control *owner);
		virtual void paint(Rect rect);
	};

//#endif
#endif

}