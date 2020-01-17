#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class Wskazowki
{
private:
	sf::Texture wskazowki;
public :
	sf::Sprite jak_grac;
	Wskazowki(float width, float height);
	~Wskazowki() {};
	void draw(sf::RenderWindow& window);
};

