#pragma once

#include <SFML/Graphics.hpp>

class AnimowanySprite : public sf::Sprite
{
private:
	int *klatki;
	int obecna_klatka;
	int ilosc_klatek;
	const int rozmiar_klatki = 64;
	sf::Time czas;

	void aktualizuj_klatke();

public:
	bool jednorazowa = false;
	float czas_klatki = 0.05f;
	bool zyje = true;

	AnimowanySprite(const sf::Texture& texture, int* klatki, int ilosc_klatek);
	~AnimowanySprite() {}
	void animuj(sf::Time nowy_czas);
};

