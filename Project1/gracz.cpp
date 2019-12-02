#include <SFML/Graphics.hpp>
#include "gracz.h"
#include "mapa.h"
#include <iostream>


Gracz::Gracz():
	ksztaltgracza(0, 0, 64, 64),//okresl obszar spritea
	ludzik(tekstura, ksztaltgracza)//utworz spritea powiazanego z tekstura
{
	tekstura.loadFromFile("tiles.png");//laduj teksture
	
	ludzik.setTextureRect(ksztaltgracza);
	ludzik.setPosition(64, 64);
}
void Gracz::draw(sf::RenderWindow& window)
{
	window.draw(ludzik);
}

void Gracz::animuj(int x, int y) {
	if (ksztaltgracza.left < x || ksztaltgracza.left > x + 128){
		ksztaltgracza.left = x;
		ludzik.setTextureRect(ksztaltgracza);
	}

	ksztaltgracza.top = y;

	if (zegar.getElapsedTime().asMilliseconds() > 65.0f) {		
		if (ksztaltgracza.left == x + 128)
			ksztaltgracza.left = x;
		else
			ksztaltgracza.left += 64;//przemieszczaj sie w poziomie tekstury

		ludzik.setTextureRect(ksztaltgracza);
		std::cout << "Klatka nr: " << ksztaltgracza.left / 64 << std::endl;
		zegar.restart();
	}
}