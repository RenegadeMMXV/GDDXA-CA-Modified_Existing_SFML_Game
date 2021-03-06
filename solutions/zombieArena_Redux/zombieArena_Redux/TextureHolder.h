/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

#include <assert.h>
#include <map>

#include <SFML/Graphics.hpp>

class TextureHolder {
public:
	TextureHolder();
	static sf::Texture& GetTexture(std::string const& filename);

private:
	// A map container from the STL,
	// that holds related pairs of String and Texture
	std::map<std::string, sf::Texture> m_Textures;

	// A pointer of the same type as the class itself
	// the one and only instance
	static TextureHolder* m_s_Instance;
};

#endif // TEXTUREHOLDER_H