#pragma once

#define TEXTURE_CLASS

namespace cj {

class PointerMap : public Object {
public:
	map<string, Object*> pars;
	PointerMap();
	virtual ~PointerMap();

	virtual void add(String name, Object* value);
	virtual void insert(String name, Object* value);
	virtual void clear();
	virtual int getCount();
	virtual Object* getValue(String name);
	virtual String getName(int index);
	virtual Object* getValue(int index);
};


class SpriteClass : public Object {
public:
	SpriteClass();

};

class Texture {
public:
	Texture();
	virtual bool loadFromFile(String fileName) = 0;
	virtual bool loadConfig(String fileName);
private:
	void getCLSC(String s, String &clss, String &layer, String &state, String &cadr);
};

}