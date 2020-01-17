#include "Przeciwnik.h"

#include "mapa.h"
#include <iostream>


Przeciwnik::Przeciwnik() :
	
	ksztaltwroga(0, 0, 64, 64),//okresl obszar spritea
	wrog(tekstura, ksztaltwroga)//utworz spritea powiazanego z tekstura
{
	predkosc = 160; //predkosc gracza w pikselach na sekunde
	tekstura.loadFromFile("tiles.png");//laduj teksture
	rodzaj = ((std::rand() % 7) + 15);
	wrog.setTextureRect(ksztaltwroga);
	wrog.setPosition(832, 576);
}
void Przeciwnik::draw(sf::RenderWindow& window)
{
	window.draw(wrog);
}

void Przeciwnik::animuj() {

	ksztaltwroga.top = rodzaj*64;

	if (zegar.getElapsedTime().asMilliseconds() > 65.0f) {
		if (ksztaltwroga.left == 320)
			ksztaltwroga.left = 0;
		else
			ksztaltwroga.left += 64;//przemieszczaj sie w poziomie tekstury

		wrog.setTextureRect(ksztaltwroga);

		zegar.restart();
	}
}
