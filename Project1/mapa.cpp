#include"mapa.h"

Mapa::Mapa(int rozmiar_x, int rozmiar_y) {
	//TODO: powinno byæ sprawdzanie b³êdu!
	textura_kafelkow.loadFromFile("tiles.png");
	rozmiar_mapy_x = rozmiar_x;
	rozmiar_mapy_y = rozmiar_y;

	//dynamiczne tworzenie tablic kafelków
	pola_mapy = new pole * [rozmiar_y];
	for (int y = 0; y < rozmiar_mapy_y; ++y) {
		pola_mapy[y] = new pole[rozmiar_mapy_x];

		for (int x = 0; x < rozmiar_mapy_x; x++) {
			//ustawianie prostok¹ta tekstury w ca³ym spritesheet
			pola_mapy[y][x].ksztalt_wewnetrzny = sf::IntRect(256, 192, 64, 64);

			//ustawianie prostok¹tów na ekranie
			pola_mapy[y][x].ksztalt.setPosition(sf::Vector2f(64 * x, 64 * y));
			pola_mapy[y][x].ksztalt.setSize(sf::Vector2f(64, 64));

			//³¹czenie tekstury z prostok¹tami
			pola_mapy[y][x].ksztalt.setTexture(&textura_kafelkow);
			pola_mapy[y][x].ksztalt.setTextureRect(pola_mapy[y][x].ksztalt_wewnetrzny);

			//domyslne ustawienia pola
			pola_mapy[y][x].destroyable = false; //false == 1
			pola_mapy[y][x].go_trough = true;

			//generowanie mapy
			// if (y == 0 || x == 0){
			//   //na pewno sta³y blok
			// }
		}
	}

	//testowanie kafelków
	pola_mapy[1][3].ksztalt_wewnetrzny = sf::IntRect(0, 192, 64, 64); // zmiania teksturki
	pola_mapy[1][6].ksztalt_wewnetrzny = sf::IntRect(0, 192, 64, 64);
	pola_mapy[2][3].ksztalt_wewnetrzny = sf::IntRect(0, 192, 64, 64);
	pola_mapy[4][9].ksztalt_wewnetrzny = sf::IntRect(0, 192, 64, 64);
	pola_mapy[5][5].ksztalt_wewnetrzny = sf::IntRect(0, 192, 64, 64);

	pola_mapy[1][3].ksztalt.setTextureRect(pola_mapy[1][3].ksztalt_wewnetrzny); // "zatwierdzenie"
	pola_mapy[1][6].ksztalt.setTextureRect(pola_mapy[1][6].ksztalt_wewnetrzny);
	pola_mapy[2][3].ksztalt.setTextureRect(pola_mapy[2][3].ksztalt_wewnetrzny);
	pola_mapy[4][9].ksztalt.setTextureRect(pola_mapy[4][9].ksztalt_wewnetrzny);
	pola_mapy[5][5].ksztalt.setTextureRect(pola_mapy[5][5].ksztalt_wewnetrzny);

}

Mapa::~Mapa() {
	//usuwanie dynamicznie utworzonej tablicy 2D
	for (int i = 0; i < rozmiar_mapy_y; ++i) {
		delete pola_mapy[i];
	}
	delete[] pola_mapy;
}

void Mapa::rysuj(sf::RenderWindow& window) {
	for (int y = 0; y < rozmiar_mapy_y; ++y) {
		for (int x = 0; x < rozmiar_mapy_x; x++) {
			window.draw(pola_mapy[y][x].ksztalt);
		}
	}
}