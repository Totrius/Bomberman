#pragma once
#include <SFML/Graphics.hpp>

typedef struct {
	bool czy_przechodzi; //czy mo�na przechodzi� przez klocek?
	bool czy_zniszczalny; //czy klocek mo�na zniszczy�?

	sf::RectangleShape ksztalt; //kszta�t protosk�ta na ekranie
	sf::IntRect ksztalt_wewnetrzny; //kszta�t prostok�ta wewn�trz tekstury
} pole;

class Mapa {
public:
	void rysuj(sf::RenderWindow& window);
	Mapa(int rozmiar_x, int rozmiar_y);
	~Mapa();
	sf::Vector2i piksele_na_wspolrzedne(int x, int y);
	pole pobierz_pole(int x, int y);
private:
	pole zwroc_cegly(int x, int y);
	pole zwroc_blok(int x, int y);
	pole zwroc_pusty(int x, int y);



	int rozmiar_mapy_x;
	int rozmiar_mapy_y;

	sf::Texture textura_kafelkow;

	pole** pola_mapy;
};