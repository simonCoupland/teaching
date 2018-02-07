/**
@file textureLoader.cpp
*/

#include "textureLoader.h"

TextureLoader * TextureLoader::psm_instance = NULL;

TextureLoader::TextureLoader()
{
	// Load textures from file
	m_textures.resize(2);

	m_textures[0] = new sf::Texture();
	m_textures[0]->loadFromFile(".\\assets\\background.bmp");

	m_textures[1] = new sf::Texture();
	m_textures[1]->loadFromFile(".\\assets\\ball.png");
}

TextureLoader * TextureLoader::instance() 
{
	if(psm_instance == NULL)
	{
		psm_instance = new TextureLoader();
	}
	return psm_instance;
}

sf::Texture * TextureLoader::getTexture(int p_index)
{
	if(p_index >= 0 && p_index < m_textures.size()) return m_textures[p_index];
	return NULL;
}