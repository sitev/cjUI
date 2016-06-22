#include "cjUI.h"

namespace cj {

Sprite::Sprite(Control *owner) : Control(owner) {
}

void Sprite::paint(Rect rect) {
	canvas->sprite(rect, *this);
}

}

