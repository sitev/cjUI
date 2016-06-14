#pragma once

#define TEXTURE_CLASS

namespace cj {

class Texture {
public:
	Texture();
	virtual bool loadFromFile(String fileName) = 0;
};

}