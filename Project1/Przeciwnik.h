#pragma once
#include <SFML/Graphics.hpp>
#include "mapa.h"
#include <iostream>

class Przeciwnik
{
private:
	int rodzaj;
	sf::Texture tekstura;
	int x, y;
public:
	sf::Clock zegar;
	sf::Sprite wrog;
	sf::IntRect ksztaltwroga;
	int predkosc = 160; //predkosc przeciwnika w pikselach na sekunde

	Przeciwnik();
	~Przeciwnik() {};

	void animuj();
	void draw(sf::RenderWindow& window);

	void setPosition(sf::Vector2f vec);
	void move(sf::Vector2f vec);
};

