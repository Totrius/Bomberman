#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "postac.h"

void gracz()
{
	sf::Event event;
	sf::Texture tekstura;
	tekstura.loadFromFile("tiles.png");//laduj teksture

	sf::IntRect ksztaltgracza(0, 0, 64, 64);//okresl obszar spritea
	sf::Sprite gracz(tekstura, ksztaltgracza);//utworz spritea powiazanego z tekstura
	sf::Clock zegar;
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
					gracz.move(sf::Vector2f(0.0f, -10.0f));
					ksztaltgracza.top = 64;
					ksztaltgracza.left = 192;
				}
				if (event.key.code == sf::Keyboard::S)
				{
					gracz.move(sf::Vector2f(0.0f, 10.0f));
					ksztaltgracza.top = 0;
					ksztaltgracza.left = 192;
				}
				if (event.key.code == sf::Keyboard::A)
				{
					gracz.move(sf::Vector2f(-10.0f, 0.0f));
					ksztaltgracza.top = 0;
					ksztaltgracza.left = 0;
				}
				if (event.key.code == sf::Keyboard::D)
				{
					gracz.move(sf::Vector2f(10.0f, 0.0f));
					ksztaltgracza.top = 64;
					ksztaltgracza.left = 0;
				}
				if (event.key.code == sf::Keyboard::W ||
					event.key.code == sf::Keyboard::A ||
					event.key.code == sf::Keyboard::S ||
					event.key.code == sf::Keyboard::D) {
					if (zegar.getElapsedTime().asMilliseconds() > 300.0f) {
						if (ksztaltgracza.left == 128)
							ksztaltgracza.left = 0;
						else if (ksztaltgracza.left == 320)
							ksztaltgracza.left = 192;
						else
							ksztaltgracza.left += 64;//przemieszczaj sie w poziomie tekstury
						gracz.setTextureRect(ksztaltgracza);
						zegar.restart();
					}
				}

			}
		}

		//rysowanie z buforowaniem 
		// czysci okno, wypelniajac kolorem
		window.clear(sf::Color::Yellow);
		window.draw(gracz);
		

		// finalizacja - wyswietlenie elementow okna
		window.display();
	}
}