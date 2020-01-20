#include"mapa.h"

Mapa::Mapa(int rozmiar_x, int rozmiar_y) {

	if (!textura_kafelkow.loadFromFile("tiles.png"))
		return; // error
	textura_kafelkow.loadFromFile("tiles.png");
	rozmiar_mapy_x = rozmiar_x;
	rozmiar_mapy_y = rozmiar_y;

	//dynamiczne tworzenie tablic kafelków
	pola_mapy = new pole * [rozmiar_x];
	for (int x = 0; x < rozmiar_mapy_x; ++x) {
		pola_mapy[x] = new pole[rozmiar_mapy_y]; // generownaie drugiego wymiaru

		for (int y = 0; y < rozmiar_mapy_y; y++) {
			pola_mapy[x][y].czy_jest_bomba = false;
			//ustawianie prostok¹ta tekstury w ca³ym spritesheet

			if (x == 0 || y == 0 || x == rozmiar_mapy_x - 1 || y == rozmiar_mapy_y - 1 || (x % 2 == 0 && y % 2 == 0)) {
				pola_mapy[x][y] = zwroc_blok(x, y);
			}
			else {
				pola_mapy[x][y] = zwroc_pusty(x, y);
			}
		}
	}
	for (int x, y, i = 0; i < 40; i++) {
		while (1) {
			x = (std::rand() % 15);
			y = (std::rand() % 11);
			if (!pola_mapy[x][y].czy_zajety) {
				pola_mapy[x][y] = zwroc_cegly(x, y);
				break;
			}
		}
	}

}

Mapa::~Mapa() {
	//usuwanie dynamicznie utworzonej tablicy 2D
	for (int i = 0; i < rozmiar_mapy_x; ++i) {
		delete pola_mapy[i];
	}
	delete[] pola_mapy;
}

void Mapa::rysuj(sf::RenderWindow& window) {
	for (int x = 0; x < rozmiar_mapy_x; ++x) {
		for (int y = 0; y < rozmiar_mapy_y; y++) {
			window.draw(pola_mapy[x][y].ksztalt);
		}
	}
}

pole Mapa::zwroc_cegly(int x, int y) {
	pole cegla;
	cegla.czy_zajety = true;
	cegla.czy_zniszczalny = true;
	cegla.czy_przechodzi = false;
	cegla.czy_jest_bomba = false;
	cegla.ksztalt.setPosition(sf::Vector2f(64 * x, 64 * y));
	cegla.ksztalt.setSize(sf::Vector2f(64, 64));
	cegla.ksztalt.setTexture(&textura_kafelkow);
	cegla.ksztalt_wewnetrzny = sf::IntRect(256, 192, 64, 64);
	cegla.ksztalt.setTextureRect(cegla.ksztalt_wewnetrzny);

	return cegla;
}
pole Mapa::zwroc_blok(int x, int y) {
	pole blok;
	blok.czy_zajety = true;
	blok.czy_zniszczalny = false;
	blok.czy_przechodzi = false;
	blok.czy_jest_bomba = false;
	blok.ksztalt.setPosition(sf::Vector2f(64 * x, 64 * y));
	blok.ksztalt.setSize(sf::Vector2f(64, 64));
	blok.ksztalt.setTexture(&textura_kafelkow);
	blok.ksztalt_wewnetrzny = sf::IntRect(192, 192, 64, 64);
	blok.ksztalt.setTextureRect(blok.ksztalt_wewnetrzny);

	return blok;
}
pole Mapa::zwroc_pusty(int x, int y) {
	pole pusty;
	if ((x == 1 && y == 1) || (x == 1 && y == 2) || (x == 2 && y == 1)) {
		pusty.czy_zajety = true;
	}
	else {
		pusty.czy_zajety = false;
	}
	pusty.czy_zniszczalny = false;
	pusty.czy_przechodzi = true;
	pusty.czy_jest_bomba = false;
	pusty.ksztalt.setPosition(sf::Vector2f(64 * x, 64 * y));
	pusty.ksztalt.setSize(sf::Vector2f(64, 64));
	pusty.ksztalt.setTexture(&textura_kafelkow);
	pusty.ksztalt_wewnetrzny = sf::IntRect(256, 256, 64, 64);
	pusty.ksztalt.setTextureRect(pusty.ksztalt_wewnetrzny);

	return pusty;
}
pole& Mapa::pobierz_pole(int x, int y) {
	if (x <= 0 || y <= 0 || x >= rozmiar_mapy_x || y >= rozmiar_mapy_y) {
		auto b = zwroc_blok(x, y);
		return b;
	}
	return pola_mapy[x][y];
}
void Mapa::ustaw_pole(int x, int y, pole& p) {
	pola_mapy[x][y] = p;
}

sf::Vector2i Mapa::piksele_na_wspolrzedne(int x, int y) {
	return sf::Vector2i(x / 64, y / 64);
}