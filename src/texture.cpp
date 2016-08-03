#include "cjUI.h"

namespace cj {

//--------------------------------------------------------------------------------------------------
//----------          PointerMap          ----------------------------------------------------------
//--------------------------------------------------------------------------------------------------

PointerMap::PointerMap() {
}

PointerMap::~PointerMap() {
}

void PointerMap::add(String name, Object* value) {
	pars.insert(std::pair<string, Object*>(name.to_string(), value));
}

void PointerMap::insert(String name, Object* value) {
	pars.insert(std::pair<string, Object*>(name.to_string(), value));
}

void PointerMap::set(String name, Object* value) {
	//Object *a = getValue(name);
	//if (a == NULL) add(name, value);
	//else 
		pars[name.to_string()] = value;
}

void PointerMap::clear() {
	pars.clear();
}
int PointerMap::getCount() {
	return pars.size();
}
Object* PointerMap::getValue(String name) {
	string z = name.to_string();
	map<string, Object*>::iterator it = pars.find(z);
	if (it == pars.end()) return NULL;
	return pars[name.to_string()];
}

String PointerMap::getName(int index) {
	auto iter = pars.begin();
	for (int i = 0; i < index; i++) iter++;
	return iter->first;
}

Object* PointerMap::getValue(int index) {
	auto iter = pars.begin();
	for (int i = 0; i < index; i++) iter++;
	return iter->second;
}

SpriteFrame::SpriteFrame(int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}



Texture::Texture() {
}

bool Texture::loadConfig(String fileName) {
	pmClass.clear();
	File *f = new File(fileName, "rb");

	while (!f->eof()) {
		String s;
		f->readLine(s);
		
		int pos = s.getPos(" = ");
		String name = s.subString(0, pos);
		string z = name.to_string();

		String clss, /*layer, */state, frame;
		getCSF(name, clss, /*layer, */state, frame);

		z = clss.to_string();
		z = state.to_string();
		SpriteClass *sc = (SpriteClass*)pmClass.getValue(clss);
		if (sc == NULL) {
			sc = new SpriteClass();
			sc->name = clss;
			pmClass.set(clss, sc);
		}
		SpriteState *ss = (SpriteState*)sc->pmState.getValue(state);
		if (ss == NULL) {
			ss = new SpriteState();
			ss->name = state;
			sc->pmState.set(state, ss);
		}

		s = s.subString(pos + 3);

		//x
		pos = s.getPos(" ");
		int x = s.subString(0, pos).toInt();
		s = s.subString(pos + 1);

		//y
		pos = s.getPos(" ");
		int y = s.subString(0, pos).toInt();
		s = s.subString(pos + 1);

		//w
		pos = s.getPos(" ");
		int w = s.subString(0, pos).toInt();
		s = s.subString(pos + 1);

		//h
		pos = s.getPos(" ");
		int h = s.subString(0, pos).toInt();
		s = s.subString(pos + 1);

		SpriteFrame *sf = (SpriteFrame*)ss->pmFrame.getValue(frame);
		if (sf == NULL) {
			sf = new SpriteFrame(x, y, w, h);
			sf->name = frame;
			ss->pmFrame.set(frame, sf);
		}
	}

	delete f;

	return true;
}

void Texture::getCSF(String s, String &clss, /*String &layer, */String &state, String &frame) {
	//cadr
	int pos = s.getPos("-");
	if (pos >= 0) frame = s.subString(pos + 1);
	else frame = "0";
	s = s.subString(0, pos);

	//class
	pos = s.getPos("_");
	if (pos >= 0) clss = s.subString(0, pos);
	else {
		clss = s;
		//layer = "";
		state = "";
		return;
	}
	s = s.subString(pos + 1);

	//state
	pos = s.getPos("_");
	if (pos >= 0) state = s.subString(pos + 1);
	else {
		state = s;
		//layer = "";
		return;
	}
	s = s.subString(0, pos);

	//layer. if LEXX want layer
	//layer = s;


	string z = s.to_string();
	z = frame.to_string();
}


}