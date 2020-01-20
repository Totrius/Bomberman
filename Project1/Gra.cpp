#include "Gra.h"
#include <iostream>

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
}

void Gra::rysuj(sf::RenderWindow& window) {
	mapa.rysuj(window);
	gracz.draw(window);

	for (auto& przeciwnik : lista_przeciwnikow)
		przeciwnik.draw(window);

	for (auto& bomba : lista_bomb)
		bomba.rysuj(window);

	for (auto& wybuch : wybuchy)
		if (wybuch.zyje)
			window.draw(wybuch);

	//std::cout << lista_bomb.size() << std::endl;
}
void Gra::aktualizuj() {
	odstep_czasu = global_clock.restart();

	for (auto& przeciwnik : lista_przeciwnikow)
		przeciwnik.animuj(odstep_czasu);

	ruch_gracza();
	aktualizacja_bomb();

	//usun wypalone wybuchy
	auto sprite_wybuch = wybuchy.begin();
	while (sprite_wybuch != wybuchy.end())
		if (sprite_wybuch->zyje == false) {
			wybuchy.erase(sprite_wybuch++);
		}
		else {
			sprite_wybuch->animuj(odstep_czasu);
			++sprite_wybuch;
		}
}

void Gra::utworz_ogien(int x, int y, int* klatki)
{
	auto wybuch_srodek = AnimowanySprite(spritesheet, klatki, klatki_wybuch_ilosc);
	wybuch_srodek.setPosition(x * 64, y * 64);
	wybuch_srodek.jednorazowa = true;
	wybuchy.push_back(wybuch_srodek);
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

			utworz_ogien(x, y, klatki_wybuch_srodek);

			wspolrzedne_ognia[ilosc_ogni++] = { x, y };
			//badaj w górê
			for (int cy = y - 1; cy >= y - moc; --cy) {
				auto blok = mapa.pobierz_pole(x, cy);
				if (blok.czy_zajety && !blok.czy_zniszczalny) {
					break;
				}
				else {
					wspolrzedne_ognia[ilosc_ogni++] = { x, cy };
					utworz_ogien(x, cy, klatki_wybuch_pionowo);
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
					utworz_ogien(x, cy, klatki_wybuch_pionowo);
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
					utworz_ogien(cx, y, klatki_wybuch_poziomo);
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
					utworz_ogien(cx, y, klatki_wybuch_poziomo);
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