#include "Przeciwnik.h"

Przeciwnik::Przeciwnik(sf::Texture& tekstura, int* klatki, int ilosc_klatek) :
	sprite(tekstura, klatki, ilosc_klatek)
{
	sprite.czas_klatki = 0.1;
}
void Przeciwnik::update(sf::Time czas)
{
	sprite.animuj(czas);

	moj_czas += czas;

	if (moj_czas.asSeconds() > czas_reakcji) {
		zmien_kierunek();
		moj_czas = moj_czas.Zero;
	}
}
void Przeciwnik::zmien_kierunek()
{
	kierunek = rand() % 4;
}
void Przeciwnik::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Przeciwnik::setPosition(sf::Vector2f vec) {
	x = vec.x;
	y = vec.y;
	sprite.setPosition(vec);
}
void Przeciwnik::move(sf::Vector2f vec) {
	x += vec.x;
	y += vec.y;
	sprite.move(vec);
}