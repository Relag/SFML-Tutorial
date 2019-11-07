#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace std;
using namespace sf;

class TextureHolder {
private:
	//Map container holding related string and texture pairs
	std::map<std::string, Texture> m_Textures;
	static TextureHolder* m_s_Instance;
	

public:
	TextureHolder();
	static Texture& GetTexture(string const& filename);
	
};

#endif TEXTURE_HOLDER_H
