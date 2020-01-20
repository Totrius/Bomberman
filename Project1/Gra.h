#pragma once
#include "gracz.h"
#include "Bomba.h"
#include "mapa.h"
#include "Przeciwnik.h"
#include "sterowanie.h"
#include "AnimowanySprite.h"
#include <SFML/Graphics.hpp>
#include <list>
class Gra
{
public:
	Gra();
	~Gra() {
		delete klatki_wybuch_srodek;
	};
	bool czy_kolizja(float x1, float y1, float x2, float y2);
	bool czy_kolizja(sf::Vector2f p1, sf::Vector2f p2);
	void rysuj(sf::RenderWindow &window);
	void aktualizuj();
	void ruch_gracza();
	void stworz_bombe(int x, int y, int moc);
	Sterowanie* stery_bajery;

private:

	void dodaj_przeciwnika();
	void utworz_ogien(int x, int y, int *klatki);
	void aktualizacja_bomb();

	Gracz gracz;
	Mapa mapa;

	const int klatki_wybuch_ilosc = 7;
	int *klatki_wybuch_srodek;
	int *klatki_wybuch_poziomo;
	int *klatki_wybuch_pionowo;

	std::list<Przeciwnik> lista_przeciwnikow;
	std::list<Bomba> lista_bomb;
	std::list<AnimowanySprite> wybuchy;

	sf::Texture spritesheet;
	sf::Clock global_clock;
	sf::Time odstep_czasu;
};

