#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "postac.h"

class gracz {
private:
	sf::Texture tekstura;
public:
	sf::Sprite ludzik;
	sf::IntRect ksztaltgracza;
	gracz();
	~gracz() {};
	void animuj(int x, int y);
	void draw(sf::RenderWindow& window);

};
gracz::gracz() :
	
	ksztaltgracza(0, 0, 64, 64),//okresl obszar spritea
	ludzik(tekstura, ksztaltgracza)//utworz spritea powiazanego z tekstura
{
	tekstura.loadFromFile("tiles.png");//laduj teksture
	
}
void gracz::draw(sf::RenderWindow& window)
{

		window.draw(ludzik);
}

void gracz::animuj(int x, int y) {
	sf::Clock zegar;
	ksztaltgracza.left = x;
	ksztaltgracza.top = y;
	if (zegar.getElapsedTime().asMilliseconds() > 300.0f) {
		if (ksztaltgracza.left == x + 128) {
			ksztaltgracza.left = x;
		}
		else
			ksztaltgracza.left += 64;//przemieszczaj sie w poziomie tekstury
		ludzik.setTextureRect(ksztaltgracza);
		zegar.restart();
	}
}



void postac() {
	sf::Event event;
	
	gracz pierwszy;
	
	
	// stworz okno
	sf::RenderWindow window(sf::VideoMode(800, 600), "GRA v.01");
	// okno widoczne, dopoki nie [x]
	while (window.isOpen())
	{

		// petla sprawdzajace zdarzenia
		sf::Event event;
		while (window.pollEvent(event))
		{
			// jezeli zdarzenie zamknij - zamykamy okno
			if (event.type == sf::Event::Closed)
				window.close();


			//jezeli zdarzenie nacisnieto klawisz - przechwyc kod klawisza
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					pierwszy.ludzik.move(sf::Vector2f(0.0f, -10.0f));
					pierwszy.animuj(192, 64);
				}
				if (event.key.code == sf::Keyboard::S)
				{
					pierwszy.ludzik.move(sf::Vector2f(0.0f, 10.0f));
					pierwszy.animuj(192, 0);
				}
				if (event.key.code == sf::Keyboard::A)
				{
					pierwszy.ludzik.move(sf::Vector2f(-10.0f, 0.0f));
					pierwszy.animuj(0, 0);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					pierwszy.ludzik.move(sf::Vector2f(10.0f, 0.0f));
					pierwszy.animuj(0, 64);
				}
				
				

			}
		}

		//rysowanie z buforowaniem 
		// czysci okno, wypelniajac kolorem
		window.clear(sf::Color::Green);
		pierwszy.draw(window);
		

		// finalizacja - wyswietlenie elementow okna
		window.display();
	}
}