#include "Gra.h"
#include <iostream>

#define ILOSC_PRZECIWNIKOW 15

Gra::Gra() :
	mapa(15, 11)
{
	spritesheet.loadFromFile("tiles.png");
	global_clock.restart();

	klatki_wybuch_srodek = new int[klatki_wybuch_ilosc * 2]{ 128, 384, 448, 384, 128, 704, 448, 704, 128, 704, 448, 384, 128, 384 };
	klatki_wybuch_poziomo = new int[klatki_wybuch_ilosc * 2];
	klatki_wybuch_pionowo = new int[klatki_wybuch_ilosc * 2];

	for (int i = 0; i < klatki_wybuch_ilosc; i++)
	{
		klatki_wybuch_poziomo[i * 2] = klatki_wybuch_srodek[i * 2] - 64;
		klatki_wybuch_poziomo[i * 2 + 1] = klatki_wybuch_srodek[i * 2 + 1];
		klatki_wybuch_pionowo[i * 2] = klatki_wybuch_srodek[i * 2];
		klatki_wybuch_pionowo[i * 2 + 1] = klatki_wybuch_srodek[i * 2 + 1] - 64;
	}

	klatki_stforki = new int[12 * 7];
	for (int numer_stforka = 0; numer_stforka < 7; numer_stforka++)
	{
		int y = 960 + numer_stforka * 64;
		for (int numer_klatki = 0; numer_klatki < 6; numer_klatki++)
		{
			int x = numer_klatki * 64;
			klatki_stforki[numer_stforka * 12 + numer_klatki * 2] = x;
			klatki_stforki[numer_stforka * 12 + numer_klatki * 2 + 1] = y;
		}
	}
	for (int i = 0; i < ILOSC_PRZECIWNIKOW; i++)
	{
		dodaj_przeciwnika();
	}
}

void Gra::rysuj(sf::RenderWindow& window) {
	mapa.rysuj(window);
	gracz.draw(window);

	for (auto& przeciwnik : lista_przeciwnikow)
		przeciwnik.draw(window);

	for (auto& bomba : lista_bomb)
		bomba.rysuj(window);

	for (auto& efekt : efekty)
		if (efekt.zyje)
			window.draw(efekt);
}
void Gra::aktualizuj() {
	odstep_czasu = global_clock.restart();

	for (auto& przeciwnik : lista_przeciwnikow)
		przeciwnik.update(odstep_czasu);

	ruch_gracza();
	ruch_przeciwnikow();
	aktualizacja_bomb();

	//usun skonczone wybuchy
	auto sprite_efekt = efekty.begin();
	while (sprite_efekt != efekty.end())
		if (sprite_efekt->zyje == false) {
			efekty.erase(sprite_efekt++);
		}
		else {
			sprite_efekt->animuj(odstep_czasu);
			++sprite_efekt;
		}
}

void Gra::dodaj_efekt(int x, int y, int* klatki, int ilosc_klatek)
{
	auto nowy_efekt = AnimowanySprite(spritesheet, klatki, ilosc_klatek);
	nowy_efekt.setPosition(x, y);
	nowy_efekt.jednorazowa = true;
	efekty.push_back(nowy_efekt);
}

void Gra::aktualizacja_bomb()
{
	//zamiana pêtli for na while, gdy
	//wewn¹trz pêtli s¹ usuwane elementy listy
	auto bomba = lista_bomb.begin();
	while (bomba != lista_bomb.end()) {
		//aktualizuj bomby
		bomba->aktualizuj(odstep_czasu.asSeconds());

		if (bomba->czy_wybuchla) {
			std::cout << "BOMBA WYBUCHLA" << std::endl;
			//zniszcz ludziki
			//odpal animacje
			//stowrz krzyz smierci

			//usun bombe z listy
			int x = bomba->pobierz_pozycje_x();
			int y = bomba->pobierz_pozycje_y();
			int moc = bomba->pobierz_moc();

			mapa.pobierz_pole(x, y).czy_jest_bomba = false;
			mapa.pobierz_pole(x, y).czy_przechodzi = true;
			lista_bomb.erase(bomba++);

			//oblicz pozycje ognia
			sf::Vector2i wspolrzedne_ognia[25];
			int ilosc_ogni = 0;

			dodaj_efekt(x * 64, y * 64, klatki_wybuch_srodek, klatki_wybuch_ilosc);

			wspolrzedne_ognia[ilosc_ogni++] = { x, y };
			//badaj w górê
			for (int cy = y - 1; cy >= y - moc; --cy) {
				auto blok = mapa.pobierz_pole(x, cy);
				if (blok.czy_zajety && !blok.czy_zniszczalny) {
					break;
				}
				else {
					wspolrzedne_ognia[ilosc_ogni++] = { x, cy };
					dodaj_efekt(x * 64, cy * 64, klatki_wybuch_pionowo, klatki_wybuch_ilosc);
				}
			}

			//badaj w dó³
			for (int cy = y + 1; cy <= y + moc; ++cy) {
				auto blok = mapa.pobierz_pole(x, cy);
				if (blok.czy_zajety && !blok.czy_zniszczalny) {
					break;
				}
				else {
					wspolrzedne_ognia[ilosc_ogni++] = { x, cy };
					dodaj_efekt(x * 64, cy * 64, klatki_wybuch_pionowo, klatki_wybuch_ilosc);
				}
			}

			//badaj w lewo
			for (int cx = x - 1; cx >= x - moc; --cx) {
				auto blok = mapa.pobierz_pole(cx, y);
				if (blok.czy_zajety && !blok.czy_zniszczalny) {
					break;
				}
				else {
					wspolrzedne_ognia[ilosc_ogni++] = { cx, y };
					dodaj_efekt(cx * 64, y * 64, klatki_wybuch_poziomo, klatki_wybuch_ilosc);
				}
			}

			//badaj w prawo
			for (int cx = x + 1; cx <= x + moc; ++cx) {
				auto blok = mapa.pobierz_pole(cx, y);
				if (blok.czy_zajety && !blok.czy_zniszczalny) {
					break;
				}
				else {
					wspolrzedne_ognia[ilosc_ogni++] = { cx, y };
					dodaj_efekt(cx * 64, y * 64, klatki_wybuch_poziomo, klatki_wybuch_ilosc);
				}
			}

			//zabij gracza
			auto pozycja_gracza_px = gracz.ludzik.getPosition();
			auto pozycja_gracza_wspolrzedne = mapa.piksele_na_wspolrzedne(pozycja_gracza_px.x, pozycja_gracza_px.y);

			//debug wypisz wsp. ognia
			std::cout << "Wspolrzedne ognia: [ ";
			for (int i = 0; i < ilosc_ogni; ++i) {
				std::cout << wspolrzedne_ognia[i].x << ':' << wspolrzedne_ognia[i].y << ' ';
			}
			std::cout << "]" << std::endl;
			//debug wypisz wsp. ognia


			for (int i = 0; i < ilosc_ogni; ++i) {
				auto& ogien = wspolrzedne_ognia[i];
				if (pozycja_gracza_wspolrzedne.x == ogien.x && pozycja_gracza_wspolrzedne.y == ogien.y) {
					//trup - przegrywasz
					//TODO: przegrana						// <--------------------------
					std::cout << "Przegrales" << std::endl;
				}
			}

			//zabij przeciwników

			//zniszcz ceg³y
			for (int i = 0; i < ilosc_ogni; ++i) {
				auto& ogien = wspolrzedne_ognia[i];

				if (mapa.pobierz_pole(ogien.x, ogien.y).czy_zniszczalny) {
					auto puste_pole = mapa.zwroc_pusty(ogien.x, ogien.y);
					mapa.ustaw_pole(ogien.x, ogien.y, puste_pole);
					std::cout << "Zniszcz pole o wspl " << ogien.x << ':' << ogien.y << std::endl;
				}
			}

		}
		else {
			++bomba;
		}
	}
}

void Gra::dodaj_przeciwnika()
{
	int x, y;
	while (1) {
		x = (std::rand() % 15);
		y = (std::rand() % 11);
		if (!mapa.pobierz_pole(x, y).czy_zajety) {

			int rodzaj = rand() % 7;

			Przeciwnik bobi(spritesheet, (klatki_stforki + rodzaj * 12), 6);
			bobi.setPosition(sf::Vector2f(x * 64, y * 64));
			lista_przeciwnikow.push_back(bobi);

			break;
		}
	}
}

void Gra::ruch_przeciwnikow() {

	for (auto& przeciwnik : lista_przeciwnikow) {

		float ruch_x = 0, ruch_y = 0;

		switch (przeciwnik.kierunek) {
		case KIERUNEK_GORA: {ruch_y = -przeciwnik.predkosc; break; }
		case KIERUNEK_DOL: {ruch_y = przeciwnik.predkosc; break; }
		case KIERUNEK_LEWO: {ruch_x = -przeciwnik.predkosc; break; }
		case KIERUNEK_PRAWO: {ruch_x = przeciwnik.predkosc; break; }
		}

		ruch_x *= odstep_czasu.asSeconds();
		ruch_y *= odstep_czasu.asSeconds();

		sf::Vector2f nowa_pozycja_przeciwnika = przeciwnik.getPosition();

		nowa_pozycja_przeciwnika.y += ruch_y;
		nowa_pozycja_przeciwnika.x += ruch_x;

		sf::Vector2i pozycja_klocka1, pozycja_klocka2;

		switch (przeciwnik.kierunek) {
		case KIERUNEK_GORA: {
			pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_przeciwnika.x + 2, nowa_pozycja_przeciwnika.y);
			pozycja_klocka2 = mapa.piksele_na_wspolrzedne(nowa_pozycja_przeciwnika.x + 62, nowa_pozycja_przeciwnika.y);
			break;
		}
		case KIERUNEK_DOL: {
			pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_przeciwnika.x + 2, nowa_pozycja_przeciwnika.y + 64);
			pozycja_klocka2 = mapa.piksele_na_wspolrzedne(nowa_pozycja_przeciwnika.x + 62, nowa_pozycja_przeciwnika.y + 64);
			break;
		}
		case KIERUNEK_LEWO: {
			pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_przeciwnika.x, nowa_pozycja_przeciwnika.y + 2);
			pozycja_klocka2 = mapa.piksele_na_wspolrzedne(nowa_pozycja_przeciwnika.x, nowa_pozycja_przeciwnika.y + 62);
			break; }
		case KIERUNEK_PRAWO: {
			pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_przeciwnika.x + 64, nowa_pozycja_przeciwnika.y + 2);
			pozycja_klocka2 = mapa.piksele_na_wspolrzedne(nowa_pozycja_przeciwnika.x + 64, nowa_pozycja_przeciwnika.y + 62);
			break;
		}
		}

		if (mapa.pobierz_pole(pozycja_klocka1.x, pozycja_klocka1.y).czy_przechodzi &&
			mapa.pobierz_pole(pozycja_klocka2.x, pozycja_klocka2.y).czy_przechodzi) {
			przeciwnik.move(sf::Vector2f(ruch_x, ruch_y));
		}
		else {
			przeciwnik.zmien_kierunek();
		}

	}

}

void Gra::ruch_gracza()
{
	float ruch_x = gracz.predkosc * odstep_czasu.asSeconds();
	float ruch_y = gracz.predkosc * odstep_czasu.asSeconds();

	if (sf::Keyboard::isKeyPressed(stery_bajery->gora))
	{
		sf::Vector2f nowa_pozycja_gracza = gracz.ludzik.getPosition();
		nowa_pozycja_gracza.y -= 0.1;
		sf::Vector2i pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x + 1, nowa_pozycja_gracza.y);
		sf::Vector2i pozycja_klocka2 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x + 62, nowa_pozycja_gracza.y);
		if (mapa.pobierz_pole(pozycja_klocka1.x, pozycja_klocka1.y).czy_przechodzi &&
			mapa.pobierz_pole(pozycja_klocka2.x, pozycja_klocka2.y).czy_przechodzi) {
			gracz.ludzik.move(sf::Vector2f(0.0f, -ruch_y));
			gracz.animuj(192, 64);
		}
	}
	if (sf::Keyboard::isKeyPressed(stery_bajery->dol))
	{
		sf::Vector2f nowa_pozycja_gracza = gracz.ludzik.getPosition();
		nowa_pozycja_gracza.y += 64.1;
		sf::Vector2i pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x + 1, nowa_pozycja_gracza.y);
		sf::Vector2i pozycja_klocka2 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x + 62, nowa_pozycja_gracza.y);
		if (mapa.pobierz_pole(pozycja_klocka1.x, pozycja_klocka1.y).czy_przechodzi &&
			mapa.pobierz_pole(pozycja_klocka2.x, pozycja_klocka2.y).czy_przechodzi) {
			gracz.ludzik.move(sf::Vector2f(0.0f, ruch_y));
			gracz.animuj(192, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(stery_bajery->lewo))
	{
		sf::Vector2f nowa_pozycja_gracza = gracz.ludzik.getPosition();
		nowa_pozycja_gracza.x -= 0.1;
		sf::Vector2i pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x, nowa_pozycja_gracza.y + 1);
		sf::Vector2i pozycja_klocka2 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x, nowa_pozycja_gracza.y + 62);
		if (mapa.pobierz_pole(pozycja_klocka1.x, pozycja_klocka1.y).czy_przechodzi &&
			mapa.pobierz_pole(pozycja_klocka2.x, pozycja_klocka2.y).czy_przechodzi) {
			gracz.ludzik.move(sf::Vector2f(-ruch_x, 0.0f));
			gracz.animuj(0, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(stery_bajery->prawo))
	{
		sf::Vector2f nowa_pozycja_gracza = gracz.ludzik.getPosition();
		nowa_pozycja_gracza.x += 64.1;
		sf::Vector2i pozycja_klocka1 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x, nowa_pozycja_gracza.y + 1);
		sf::Vector2i pozycja_klocka2 = mapa.piksele_na_wspolrzedne(nowa_pozycja_gracza.x, nowa_pozycja_gracza.y + 62);
		if (mapa.pobierz_pole(pozycja_klocka1.x, pozycja_klocka1.y).czy_przechodzi &&
			mapa.pobierz_pole(pozycja_klocka2.x, pozycja_klocka2.y).czy_przechodzi) {
			gracz.ludzik.move(sf::Vector2f(ruch_x, 0.0f));
			gracz.animuj(0, 64);
		}
	}
	if (sf::Keyboard::isKeyPressed(stery_bajery->bomba)) {
		auto pozycja_w_pikselach = gracz.ludzik.getPosition();
		pozycja_w_pikselach.x += 32;
		pozycja_w_pikselach.y += 32;
		auto pozycja_w_wspolrzednych = mapa.piksele_na_wspolrzedne(pozycja_w_pikselach.x, pozycja_w_pikselach.y);

		stworz_bombe(pozycja_w_wspolrzednych.x, pozycja_w_wspolrzednych.y, 3);
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
void Gra::stworz_bombe(int x, int y, int moc) {
	if (!mapa.pobierz_pole(x, y).czy_jest_bomba && lista_bomb.size() < gracz.max_bomb) {
		Bomba bomba(x, y, moc, spritesheet);
		mapa.pobierz_pole(x, y).czy_jest_bomba = true;
		mapa.pobierz_pole(x, y).czy_przechodzi = false;
		lista_bomb.push_back(bomba);
	}
}