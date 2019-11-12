#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "test.h"



void test ()
{
	sf::Event event;
	sf::Texture tekstura;
	tekstura.loadFromFile("smok.png");//laduj teksture

	sf::IntRect ksztaltSmoka(0, 0, 200, 200);//okresl obszar spritea
	sf::Sprite smok(tekstura, ksztaltSmoka);//utworz spritea powiazanego z tekstura
	sf::Clock zegar;
	// stworz okno
	sf::RenderWindow window(sf::VideoMode(800, 600), "GRA v.01");
	sf::RectangleShape oktagon(sf::Vector2f(20.f, 20.f));
	oktagon.setFillColor(sf::Color::Cyan);
	oktagon.setPosition(100, 100);
	sf::FloatRect boundingOkta = oktagon.getGlobalBounds();
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
					smok.move(sf::Vector2f(0.0f, -10.0f));
					ksztaltSmoka.top = 600;
				}
				if (event.key.code == sf::Keyboard::S)
				{
					smok.move(sf::Vector2f(0.0f, 10.0f));
					ksztaltSmoka.top = 0;
				}
				if (event.key.code == sf::Keyboard::A)
				{
					smok.move(sf::Vector2f(-10.0f, 0.0f));
					ksztaltSmoka.top = 200;
				}
				if (event.key.code == sf::Keyboard::D)
				{
					smok.move(sf::Vector2f(10.0f, 0.0f));
					ksztaltSmoka.top = 400;
				}
				if (event.key.code == sf::Keyboard::W ||
					event.key.code == sf::Keyboard::A ||
					event.key.code == sf::Keyboard::S ||
					event.key.code == sf::Keyboard::D) {
					if (zegar.getElapsedTime().asMilliseconds() > 300.0f) {
						if (ksztaltSmoka.left == 400)//w wierszu tekstury sa 3 klatki (200 x 200px)
							ksztaltSmoka.left = 0;
						else
							ksztaltSmoka.left += 200;//przemieszczaj sie w poziomie tekstury
						smok.setTextureRect(ksztaltSmoka);
						zegar.restart();
					}
				}

			}
		}

		//rysowanie z buforowaniem 
		// czysci okno, wypelniajac kolorem
		window.clear(sf::Color::White);

		// procedura rysujaca poszczegolne obiekty w oknie
		// umieszcza obiekty w buforze
		// window.draw(...);
		window.draw(smok);
		window.draw(oktagon);

		// finalizacja - wyswietlenie elementow okna
		window.display();
	}
}
