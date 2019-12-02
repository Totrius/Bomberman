#pragma once
#include <SFML/Graphics.hpp>

class Gracz {
private:
	sf::Texture tekstura;
public:
	sf::Clock zegar;
	sf::Sprite ludzik;
	sf::IntRect ksztaltgracza;
	Gracz();
	~Gracz() {};
	void animuj(int x, int y);
	void draw(sf::RenderWindow& window);

};