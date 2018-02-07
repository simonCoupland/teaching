/**
@file textureLoader.h
*/

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SFML/Graphics.hpp>
#include <vector>

class TextureLoader
{
private:
	TextureLoader(); //!< Constructor
	static TextureLoader * psm_instance; //!< Pointer to instance of the class
	std::vector<sf::Texture *> m_textures; //!< Data structure containing textures
public:
	static TextureLoader * instance(); //!< Returns the instance of the class
	sf::Texture * getTexture(int p_index); //!< Return a pointer to a texture
};




#endif
