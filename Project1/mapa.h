#pragma once
#include <SFML/Graphics.hpp>

typedef struct {
  bool go_trough; //czy mo�na przechodzi� przez klocek?
  bool destroyable; //czy klocek mo�na zniszczy�?

  sf::RectangleShape ksztalt; //kszta�t protosk�ta na ekranie
  sf::IntRect ksztalt_wewnetrzny; //kszta�t prostok�ta wewn�trz tekstury
} pole;

class Mapa {
  public:
	void rysuj(sf::RenderWindow &window);
  Mapa(int rozmiar_x, int rozmiar_y);
  ~Mapa();

  private:
  int rozmiar_mapy_x;
  int rozmiar_mapy_y;

  sf::Texture textura_kafelkow;

  pole **pola_mapy;
};