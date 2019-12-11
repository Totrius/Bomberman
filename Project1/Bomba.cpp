#include "Bomba.h"


Bomba::Bomba(int x, int y, int moc, sf::Texture& tex) :
	x(x), y(y), moc(moc) {
	bomb.setTextureRect(sf::IntRect(0, 192, 64, 64));
	bomb.setPosition(64 * x, 64 * y);
	bomb.setTexture(tex);

}

void Bomba::aktualizuj(double czas) {
	czas_zycia += czas;

	if (czas_zycia >= czas_do_wybuchu) {
		wybuch();
	}

}
void Bomba::rysuj(sf::RenderWindow& window) {
	window.draw(bomb);
}
void Bomba::wybuch() {
	czy_wybuchla = true;
}