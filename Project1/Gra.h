#pragma once
#include "gracz.h"
#include "Bomba.h"
#include "mapa.h"
#include "Przeciwnik.h"
#include <SFML/Graphics.hpp>
#include <list>
class Gra
{
public:
	Gra();
	~Gra() {};
	bool czy_kolizja(float x1, float y1, float x2, float y2);
	bool czy_kolizja(sf::Vector2f p1, sf::Vector2f p2);
	void rysuj(sf::RenderWindow &window);
	void aktualizuj();
	void stworz_bombe(int x, int y, int moc);
	
	
private:
	Gracz gracz;
	Mapa mapa;
	Przeciwnik przeciwnik;
	std::list<Bomba> lista_bomb;
	sf::Texture spritesheet;
	sf::Clock global_clock;
	sf::Time odstep_czasu;

};

