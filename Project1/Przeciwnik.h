#pragma once
#include <SFML/Graphics.hpp>
#include "AnimowanySprite.h"

#define KIERUNEK_GORA 0
#define KIERUNEK_DOL 1
#define KIERUNEK_LEWO 2
#define KIERUNEK_PRAWO 3

class Przeciwnik
{
private:
	int rodzaj;
	float x, y;
	sf::Time moj_czas;
	const float czas_reakcji = 3.2;
	AnimowanySprite sprite;

public:
	int predkosc = 130; //predkosc przeciwnika w pikselach na sekunde
	int kierunek = 0;

	Przeciwnik(sf::Texture& tekstura, int* klatki, int ilosc_klatek);
	~Przeciwnik() {};

	void update(sf::Time czas);
	void zmien_kierunek();
	void draw(sf::RenderWindow& window);

	void setPosition(sf::Vector2f vec);
	void move(sf::Vector2f vec);

	sf::Vector2f getPosition() { return sf::Vector2f(x, y); }
};

