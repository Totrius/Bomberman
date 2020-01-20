#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#define MAX_STER 6

#define RUCH_W_GORE 1
#define RUCH_W_DOL 2
#define RUCH_W_LEWO 3
#define RUCH_W_PRAWO 4
#define RUCH_BOMBA 5

class Sterowanie
{

private:
	sf::Font font;
	sf::Text sterowanie[MAX_STER];//maksymalna liczba poziomow
	int selectedItem = 0;
	
public:
	int czekaj_na_klawisz = 0;
	sf::Keyboard::Key gora, dol, lewo, prawo, bomba;
	Sterowanie(float width, float height);
	~Sterowanie() {};
	void pobierz_sterowanie();
	void zapisz_sterowanie();
	void moveIt(int i);//przesun
	int getSelectedItem() { return selectedItem; }//zwroc poziom menu
	void draw(sf::RenderWindow& window);//rysuj menu w oknie
};
