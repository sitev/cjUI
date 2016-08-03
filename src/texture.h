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
	virtual void set(String name, Object* value);
	virtual void clear();
	virtual int getCount();
	virtual Object* getValue(String name);
	virtual String getName(int index);
	virtual Object* getValue(int index);
};


class SpriteClass : public Object {
public:
	String name;
	PointerMap pmState;
	SpriteClass() {}
};

class SpriteState : public Object {
public:
	String name;
	PointerMap pmFrame;
	SpriteState() {}
};

class SpriteFrame : public Object {
public:
	String name;
	int x, y, w, h;
	SpriteFrame(int x, int y, int w, int h);
};

class Texture {
public:
	PointerMap pmClass;
	Texture();
	virtual bool loadFromFile(String fileName) = 0;
	virtual bool loadConfig(String fileName);
private:
	void getCSF(String s, String &clss, /*String &layer, */String &state, String &frame);
};

}