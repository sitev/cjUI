#include "cjUI.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>

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

	int counter = 0;
	while (true) {
		int tick0 = GetTickCount();

		if (f->eof()) break;

		int tick1 = GetTickCount();

		String s;
		f->readLine(s);

		int tick2 = GetTickCount();
		
		int pos = s.find(" = ");
		String name = s.subString(0, pos);
		string z;// = name.to_string();

		int tick3 = GetTickCount();

		String clss, /*layer, */state, frame;
		getCSF(name, clss, /*layer, */state, frame);

		int tick4 = GetTickCount();

		z = clss.to_string();
		z = state.to_string();
		SpriteClass *sc = (SpriteClass*)pmClass.getValue(clss);
		if (sc == NULL) {
			sc = new SpriteClass();
			sc->name = clss;
			pmClass.set(clss, sc);
		}

		int tick5 = GetTickCount();

		SpriteState *ss = (SpriteState*)sc->pmState.getValue(state);
		if (ss == NULL) {
			ss = new SpriteState();
			ss->name = state;
			sc->pmState.set(state, ss);
		}

		int tick6 = GetTickCount();

		s = s.subString(pos + 3);

		int tick7 = GetTickCount();

		//x
		pos = s.getPos(" ");
		int x = s.subString(0, pos).toInt();
		s = s.subString(pos + 1);

		int tick8 = GetTickCount();

		//y
		pos = s.getPos(" ");
		int y = s.subString(0, pos).toInt();
		s = s.subString(pos + 1);

		int tick9 = GetTickCount();

		//w
		pos = s.getPos(" ");
		int w = s.subString(0, pos).toInt();
		s = s.subString(pos + 1);

		int tick10 = GetTickCount();

		//h
		pos = s.getPos(" ");
		int h = s.subString(0, pos).toInt();
		s = s.subString(pos + 1);

		int tick11 = GetTickCount();

		SpriteFrame *sf = (SpriteFrame*)ss->pmFrame.getValue(frame);
		if (sf == NULL) {
			sf = new SpriteFrame(x, y, w, h);
			sf->name = frame;
			ss->pmFrame.set(frame, sf);
		}

		int tick12 = GetTickCount();

		counter++;
		
		if (counter % 50 == 0)
			printf("%d: %d %d %d %d %d %d %d %d %d %d %d %d = %d\n", counter, 
				tick1 - tick0, tick2 - tick1, tick3 - tick2, tick4 - tick3, tick5 - tick4, tick6 - tick5, tick7 - tick6,
				tick8 - tick7, tick9 - tick8, tick10 - tick9, tick11 - tick10, tick12 - tick11, tick12 - tick1);
			
	}

	delete f;

	return true;
}

void Texture::getCSF(String s, String &clss, /*String &layer, */String &state, String &frame) {
	//cadr
	int pos = s.find("-");
	if (pos >= 0) frame = s.subString(pos + 1);
	else frame = "0";
	s = s.subString(0, pos);

	//class
	pos = s.find("_");
	if (pos >= 0) clss = s.subString(0, pos);
	else {
		clss = s;
		//layer = "";
		state = "";
		return;
	}
	s = s.subString(pos + 1);

	//state
	pos = s.find("_");
	if (pos >= 0) state = s.subString(pos + 1);
	else {
		state = s;
		//layer = "";
		return;
	}
	s = s.subString(0, pos);

	//layer. if LEXX want layer
	//layer = s;


	//string z = s.to_string();
	//z = frame.to_string();
}


}