#include "Gra.h"

Gra::Gra() :
	mapa(15, 11)
{}

void Gra::rysuj(sf::RenderWindow& window) {
	mapa.rysuj(window);
	gracz.draw(window);
}
void Gra::aktualizuj() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		sf::Vector2f nowa_pozycja_gracza = gracz.ludzik.getPosition();
		nowa_pozycja_gracza.y -= 0.1;
		sf::Vector2i pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x + 1, nowa_pozycja_gracza.y);
		sf::Vector2i pozycja_klocka2 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x + 62, nowa_pozycja_gracza.y);
		if (mapa.pobierz_pole(pozycja_klocka1.x, pozycja_klocka1.y).czy_przechodzi &&
			mapa.pobierz_pole(pozycja_klocka2.x, pozycja_klocka2.y).czy_przechodzi) {
			gracz.ludzik.move(sf::Vector2f(0.0f, -0.1));
			gracz.animuj(192, 64);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		sf::Vector2f nowa_pozycja_gracza = gracz.ludzik.getPosition();
		nowa_pozycja_gracza.y += 64.1;
		sf::Vector2i pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x+1, nowa_pozycja_gracza.y);
		sf::Vector2i pozycja_klocka2 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x+62, nowa_pozycja_gracza.y);
		if (mapa.pobierz_pole(pozycja_klocka1.x, pozycja_klocka1.y).czy_przechodzi &&
			mapa.pobierz_pole(pozycja_klocka2.x, pozycja_klocka2.y).czy_przechodzi) {
			gracz.ludzik.move(sf::Vector2f(0.0f, 0.1));
			gracz.animuj(192, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		sf::Vector2f nowa_pozycja_gracza = gracz.ludzik.getPosition();
		nowa_pozycja_gracza.x -= 0.1;
		sf::Vector2i pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x, nowa_pozycja_gracza.y+1);
		sf::Vector2i pozycja_klocka2= mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x, nowa_pozycja_gracza.y+62);
		if (mapa.pobierz_pole(pozycja_klocka1.x, pozycja_klocka1.y).czy_przechodzi &&
			mapa.pobierz_pole(pozycja_klocka2.x, pozycja_klocka2.y).czy_przechodzi) {
			gracz.ludzik.move(sf::Vector2f(-0.1, .0f));
			gracz.animuj(0, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		sf::Vector2f nowa_pozycja_gracza = gracz.ludzik.getPosition();
		nowa_pozycja_gracza.x  += 64.1;
		sf::Vector2i pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x, nowa_pozycja_gracza.y+1);
		sf::Vector2i pozycja_klocka2 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x, nowa_pozycja_gracza.y+62);
		if (mapa.pobierz_pole(pozycja_klocka1.x, pozycja_klocka1.y).czy_przechodzi && 
			mapa.pobierz_pole(pozycja_klocka2.x, pozycja_klocka2.y).czy_przechodzi) {
			gracz.ludzik.move(sf::Vector2f(0.1, 0.0f));
			gracz.animuj(0, 64);
		}
	}
}

bool Gra::czy_kolizja(float x1, float y1, float x2, float y2) {
	if ((abs(x1 - x2) > 64) && (abs(y1 - y2) > 64)) {
		return false;
	}
	return true;
}
bool Gra::czy_kolizja(sf::Vector2f p1, sf::Vector2f p2) {
	return czy_kolizja(p1.x, p1.y, p2.x, p2.y);
}