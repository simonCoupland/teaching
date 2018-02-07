#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class TextureLoader
{
private :
	std::vector<sf::Texture> textures;
	std::string baseDirectory;
public :
	TextureLoader();
	void setBaseDirectory(std::string dir);
	void load(std::vector<std::string> fileNames);
	std::vector<sf::Texture>::iterator getTextureIterator(int index);
};

#endif