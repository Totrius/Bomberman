#include "menu.h"
#include "Gra.h"
#include "Bomba.h"
#include "sterowanie.h"
#include "Wskazowki.h"
#include <fstream>
#include <cstdlib>
#include <time.h>


#define MENU_GLOWNE 0
#define MENU_OPCJE 1
#define MENU_GRA 100



int main()
{
	srand(time(NULL));
	int wybrane_menu = 0;
	bool wyswietl_pomoc = false;

	sf::Music music;
	if (!music.openFromFile("menu_theme.ogg"))
		return -1; // error
	music.setLoop(true);
	//music.play();

	sf::RenderWindow window(sf::VideoMode(1000, 800), "My Bombeer");// utworz okno

	Menu menu(window.getSize().x, window.getSize().y);
	Sterowanie sterowanie(window.getSize().x, window.getSize().y);
	sterowanie.pobierz_sterowanie();
	Wskazowki wskazowki(window.getSize().x, window.getSize().y);
	Gra gra;
	gra.stery_bajery = &sterowanie;

	// petla wieczna - dopoki okno jest otwarte
	sf::Event event;
	while (window.isOpen())
	{
		// w kazdej iteracji petli sprawdzaj zdarzenia
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();

			//jezeli nacisnieto jakikolwiek przycisk
			if (event.type == sf::Event::KeyPressed)
			{//obsluga menu z poziomu klawiszy (strzalki)
				if (event.key.code == sf::Keyboard::Up)
				{
					if (wybrane_menu == MENU_GLOWNE) {
						menu.moveIt(-1);
					}
					else if (wybrane_menu == MENU_OPCJE && sterowanie.czekaj_na_klawisz == 0) {
						sterowanie.moveIt(-1);
					}
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					if (wybrane_menu == MENU_GLOWNE) {
						menu.moveIt(1);
					}
					else if (wybrane_menu == MENU_OPCJE && sterowanie.czekaj_na_klawisz == 0) {
						sterowanie.moveIt(1);
					}
				}
				switch (wybrane_menu) {
				case MENU_GLOWNE: {
					//uruchamianie procedur na skutek wyboru menu (wybor poziomu menu to ENTER))
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						std::cout << "Uruchamiam gre..." << std::endl;
						wybrane_menu = MENU_GRA;
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
					{
						wybrane_menu = MENU_OPCJE;

						std::cout << "Sterowanie " << wybrane_menu << std::endl;

					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
					{
						std::cout << "Koniec gry..." << std::endl;
						window.close();
					}
					break;
				}
				case MENU_OPCJE: {
					if (sterowanie.czekaj_na_klawisz != 0) {
						switch (sterowanie.czekaj_na_klawisz) {
						case RUCH_BOMBA: { sterowanie.bomba = event.key.code; sterowanie.czekaj_na_klawisz = 0; break; }
						case RUCH_W_GORE: { sterowanie.gora = event.key.code; sterowanie.czekaj_na_klawisz = 0; break; }
						case RUCH_W_DOL: { sterowanie.dol = event.key.code; sterowanie.czekaj_na_klawisz = 0; break; }
						case RUCH_W_LEWO: { sterowanie.lewo = event.key.code; sterowanie.czekaj_na_klawisz = 0; break; }
						case RUCH_W_PRAWO: { sterowanie.prawo = event.key.code; sterowanie.czekaj_na_klawisz = 0; break; }
						}
					}
					else {
						if (event.key.code == sf::Keyboard::Enter && sterowanie.getSelectedItem() == 0)
							sterowanie.czekaj_na_klawisz = RUCH_W_GORE;
						if (event.key.code == sf::Keyboard::Enter && sterowanie.getSelectedItem() == 1)
							sterowanie.czekaj_na_klawisz = RUCH_W_DOL;
						if (event.key.code == sf::Keyboard::Enter && sterowanie.getSelectedItem() == 2)
							sterowanie.czekaj_na_klawisz = RUCH_W_LEWO;
						if (event.key.code == sf::Keyboard::Enter && sterowanie.getSelectedItem() == 3)
							sterowanie.czekaj_na_klawisz = RUCH_W_PRAWO;
						if (event.key.code == sf::Keyboard::Enter && sterowanie.getSelectedItem() == 4)
							sterowanie.czekaj_na_klawisz = RUCH_BOMBA;

						if (event.key.code == sf::Keyboard::Enter && sterowanie.getSelectedItem() == 5) {
							wybrane_menu = MENU_GLOWNE;
							sterowanie.zapisz_sterowanie();
						}
					}
					break;
				}
				}
				if (event.key.code == sf::Keyboard::F1 && wybrane_menu == MENU_GRA) {
					wyswietl_pomoc = !wyswietl_pomoc;
				}
			}
		}


		if (wybrane_menu == MENU_GRA && !wyswietl_pomoc) {
			gra.aktualizuj();
		}

		// wyczysc obszar rysowania
		window.clear(sf::Color::Green);

		// tutaj umiesc procedury rysujace...
		if (wybrane_menu == MENU_GLOWNE) {
			menu.draw(window);
		}
		if (wybrane_menu == MENU_GRA) {

			if (wyswietl_pomoc) {
				wskazowki.draw(window);
			}
			else
			{
				gra.rysuj(window);
			}
		}
		if (wybrane_menu == MENU_OPCJE) {
			sterowanie.draw(window);
		}


		// ostatnia czynnosc - wyswietl okno wraz zawartoscia
		window.display();
	}

	return 0;
}