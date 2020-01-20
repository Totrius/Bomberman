#include "Przeciwnik.h"

Przeciwnik::Przeciwnik() :
	ksztaltwroga(0, 0, 64, 64),//okresl obszar spritea
	wrog(tekstura, ksztaltwroga)//utworz spritea powiazanego z tekstura
{
	tekstura.loadFromFile("tiles.png");//laduj teksture
	rodzaj = ((std::rand() % 7) + 15);
	wrog.setTextureRect(ksztaltwroga);
	

	// while (1) {
	// 	x = (std::rand() % 15);
	// 	y = (std::rand() % 11);
	// 	if (!gra.mapa.pobierz_pole(x, y).czy_zajety) {
	// 		wrog.setPosition(x*64, y*64);
	// 		break;
	// 	}
	// }
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

void Przeciwnik::setPosition(sf::Vector2f vec){
	wrog.setPosition(vec);
}
void Przeciwnik::move(sf::Vector2f vec){
	wrog.move(vec);
}