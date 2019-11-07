#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename) {
	//Get Reference to m_Textures using m_s_Instance
	auto& m = m_s_Instance->m_Textures;
	
	auto keyValuePair = m.find(filename);
	
	if (keyValuePair != m.end()) {
		//yes, return the texture
		return keyValuePair->second;
	}
	else {
		//filename not found, create new key value pair
		auto& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}
	
}