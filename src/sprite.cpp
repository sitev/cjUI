#include "cjUI.h"

namespace cj {

Sprite::Sprite(Control *owner) : Control(owner) {
}

void Sprite::paint(Rect rect) {
	if (animate) {
		int count = ss->pmFrame.getCount();
		if (count >= 2) {
			if (startAnimate) {
				saveTick = GetTickCount();
				startAnimate = false;
			}
			int tick = GetTickCount();
			int delta = tick - saveTick;
			if (delta >= interval) {
				saveTick = tick;
				int frame = sf->name.toInt();
				frame++;
				if (frame >= count) frame = 0;
				this->setFrame(frame);
			}
		}
	}
	canvas->sprite(rect, *this);
}

void Sprite::setClass(String value) {
	if (tx == nullptr) return;
	
	sc = (SpriteClass*)tx->pmClass.getValue(value);
}

void Sprite::setState(String value) {
	if (sc == nullptr) return;

	ss = (SpriteState*)sc->pmState.getValue(value);
	setFrame("0");
}

void Sprite::setFrame(String value) {
	if (ss == nullptr) return;

	sf = (SpriteFrame*)ss->pmFrame.getValue(value);
}

void Sprite::setInterval(int msec) {
	interval = msec;
}
void Sprite::setAnimate(bool value) {
	animate = value;
	startAnimate = true;
}




}

