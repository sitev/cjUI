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

void PointerMap::clear() {
	pars.clear();
}
int PointerMap::getCount() {
	return pars.size();
}
Object* PointerMap::getValue(String name) {
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


Texture::Texture() {
}

bool Texture::loadConfig(String fileName) {
	File *f = new File(fileName, "rb");

	while (!f->eof()) {
		String s;
		f->readLine(s);
		
		int pos = s.getPos(" = ");
		String name = s.subString(0, pos);
		string z = name.to_string();

		String clss, layer, state, cadr;
		getCLSC(name, clss, layer, state, cadr);

		/* test
		string s_name = name.to_string(), s_clss = clss.to_string(), s_layer = layer.to_string(), 
			s_state = state.to_string(), s_cadr = cadr.to_string();
		printf("name = %s\n", s_name.c_str());
		printf("class = %s\n", s_clss.c_str());
		printf("layer = %s\n", s_layer.c_str());
		printf("state = %s\n", s_state.c_str());
		printf("cadr = %s\n", s_cadr.c_str());
		*/

		s = s.subString(pos + 3);
		z = s.to_string();

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

		//break;
	}

	delete f;

	return true;
}

void Texture::getCLSC(String s, String &clss, String &layer, String &state, String &cadr) {
	//cadr
	int pos = s.getPos("-");
	if (pos >= 0) cadr = s.subString(pos + 1);
	else cadr = "";
	s = s.subString(0, pos);

	//class
	pos = s.getPos("_");
	if (pos >= 0) clss = s.subString(0, pos);
	else {
		clss = s;
		layer = "";
		state = "";
		return;
	}
	s = s.subString(pos + 1);

	//state
	pos = s.getPos("_");
	if (pos >= 0) state = s.subString(pos + 1);
	else {
		state = s;
		layer = "";
		return;
	}
	s = s.subString(0, pos);

	//layer
	layer = s;


	string z = s.to_string();
	z = cadr.to_string();
}


}