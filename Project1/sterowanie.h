#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#define MAX_STER 5
class Sterowanie
{

private:
	sf::Font font;
	sf::Text sterowanie[MAX_STER];//maksymalna liczba poziomow
	int selectedItem = 0;
	


public:
	std::string gora, dol, lewo, prawo, nowe_w, nowe_s, nowe_a, nowe_d;
	Sterowanie(float width, float height);
	~Sterowanie() {};
	void pobierz_sterowanie(std::string a, std::string b, std::string c, std::string d);
	void zmien_sterowanie(std::string a, std::string b, std::string c, std::string d);
	void moveIt(int i);//przesun
	int getSelectedItem() { return selectedItem; }//zwroc poziom menu
	void draw(sf::RenderWindow& window);//rysuj menu w oknie
};
