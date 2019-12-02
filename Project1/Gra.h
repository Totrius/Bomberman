#pragma once
#include "gracz.h"
#include "mapa.h"
#include <SFML/Graphics.hpp>
class Gra
{
public:
	Gra();
	~Gra() {};
	bool czy_kolizja(float x1, float y1, float x2, float y2);
	bool czy_kolizja(sf::Vector2f p1, sf::Vector2f p2);

	void rysuj(sf::RenderWindow &window);
	void aktualizuj();
private:
	Gracz gracz;
	Mapa mapa;
};

