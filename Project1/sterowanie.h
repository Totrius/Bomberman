#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#define MAX_STER 5
class Sterowanie
{

private:
	sf::Font font;
	sf::Text sterowanie[MAX_STER];//maksymalna liczba poziomow
	int selectedItem = 0;


public:
	Sterowanie(float width, float height);
	~Sterowanie() {};
	void moveIt(int i);//przesun
	int getSelectedItem() { return selectedItem; }//zwroc poziom menu
	void draw(sf::RenderWindow& window);//rysuj menu w oknie
};
