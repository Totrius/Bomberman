#include <SFML/Graphics.hpp>
#include "postac.h"
#include "mapa.h"
#include <iostream>

class gracz {
private:
	sf::Texture tekstura;
public:
	sf::Clock zegar;
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
	
	ludzik.setTextureRect(ksztaltgracza);
	ludzik.setPosition(0, 0);
}
void gracz::draw(sf::RenderWindow& window)
{

	window.draw(ludzik);

}

void gracz::animuj(int x, int y) {
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

void postac() {
	sf::Event event;
	gracz pierwszy;
	Mapa mapka(10, 6);

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
					pierwszy.ludzik.move(sf::Vector2f(0.0f, -5.0f));
					pierwszy.animuj(192, 64);
				}
				if (event.key.code == sf::Keyboard::S)
				{
					pierwszy.ludzik.move(sf::Vector2f(0.0f, 5.0f));
					pierwszy.animuj(192, 0);
				}
				if (event.key.code == sf::Keyboard::A)
				{
					pierwszy.ludzik.move(sf::Vector2f(-5.0f, .0f));
					pierwszy.animuj(0, 0);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					pierwszy.ludzik.move(sf::Vector2f(5.0f, 0.0f));
					pierwszy.animuj(0, 64);
				}
			}
		}

		//rysowanie z buforowaniem 
		// czysci okno, wypelniajac kolorem
		window.clear(sf::Color::Green);
		
		mapka.rysuj(window);
		pierwszy.draw(window);

		// finalizacja - wyswietlenie elementow okna
		window.display();
	}
}