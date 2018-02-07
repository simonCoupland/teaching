#include "textureLoader.h"

TextureLoader::TextureLoader()
{
	
}

void TextureLoader::setBaseDirectory(std::string dir)
{
	baseDirectory = dir;
}

void TextureLoader::load(std::vector<std::string> fileNames)
{
	std::vector<std::string>::iterator str_itr;
	sf::Texture texture;
	for(str_itr = fileNames.begin(); str_itr != fileNames.end(); ++str_itr)
	{
		texture.loadFromFile(baseDirectory + (*str_itr));
		textures.push_back(texture);
	}
}

std::vector<sf::Texture>::iterator TextureLoader::getTextureIterator(int index)
{
	return textures.begin()+index;
}