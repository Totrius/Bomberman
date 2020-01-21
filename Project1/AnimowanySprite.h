#pragma once

#include <SFML/Graphics.hpp>

class AnimowanySprite : public sf::Sprite
{
private:
	int obecna_klatka = 0;
	const int rozmiar_klatki = 64;
	sf::Time czas;
	void aktualizuj_klatke();

public:
	bool jednorazowa = false;
	float czas_klatki = 0.05f;
	bool zyje = true;
	int ilosc_klatek = 0;
	int* klatki = nullptr;

	AnimowanySprite() {};
	AnimowanySprite(const sf::Texture& texture, int* klatki, int ilosc_klatek);
	void setTexture(const sf::Texture& texture, bool resetRect = false);
	~AnimowanySprite() {}
	void animuj(sf::Time nowy_czas);
};

