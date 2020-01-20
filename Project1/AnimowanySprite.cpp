#include "AnimowanySprite.h"
#include <iostream>

void AnimowanySprite::aktualizuj_klatke()
{
	Sprite::setTextureRect(
		sf::IntRect(
			klatki[obecna_klatka * 2],
			klatki[obecna_klatka * 2 + 1],
			rozmiar_klatki, rozmiar_klatki
		));

	
}

AnimowanySprite::AnimowanySprite(const sf::Texture& texture, int* klatki, int ilosc_klatek) :
	sf::Sprite(texture)
{
	this->klatki = klatki;
	this->ilosc_klatek = ilosc_klatek;
	aktualizuj_klatke();
}

void AnimowanySprite::animuj(sf::Time nowy_czas)
{
	if (!zyje) return;

	czas += nowy_czas;

	if (czas.asSeconds() >= czas_klatki) {

		obecna_klatka = (obecna_klatka + 1) % ilosc_klatek;

		if (obecna_klatka == 0 && jednorazowa) {
			obecna_klatka = ilosc_klatek - 1;
			zyje = false;
			return;
		}

		aktualizuj_klatke();

		czas = czas.Zero;
	}
}
