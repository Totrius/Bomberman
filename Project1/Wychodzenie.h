#pragma once
#include <SFML/Graphics.hpp>
class Wychodzenie
{
private:
	sf::Texture wychodzenie;
public:
	sf::Sprite czy_wyjsc;
	Wychodzenie(float width, float height);
	~Wychodzenie() {};
	void draw(sf::RenderWindow& window);
};

