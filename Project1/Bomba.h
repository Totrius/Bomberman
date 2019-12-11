#pragma once
#include <SFML/Graphics.hpp>


class Bomba
{
public:
	Bomba(int x, int y, int moc, sf::Texture& tex);
	~Bomba() {};
	void rysuj(sf::RenderWindow& window);
	bool czy_wybuchla = false;

	int pobierz_pozycje_x() { return x; }
	int pobierz_pozycje_y() { return y; }

	void aktualizuj(double czas);
private:
	int x;
	int y;
	int moc;
	double czas_zycia = 0.0;
	const double czas_do_wybuchu = 3;
	sf::Sprite bomb;

	void wybuch();


};

