#include "menu.h"
#include "Gra.h"
#include "Bomba.h"
#include "sterowanie.h"
#include <fstream>
#include <cstdlib>




int main()
{
	



	int wybrane_menu = 0;

	sf::Music music;
	if (!music.openFromFile("menu_theme.ogg"))
		return -1; // error
	music.setLoop(true);
	music.play();

	

	sf::RenderWindow window(sf::VideoMode(1000, 800), "My Bombeer");// utworz okno

	Menu menu(window.getSize().x, window.getSize().y);
	Sterowanie sterowanie(window.getSize().x, window.getSize().y);
	Gra gra;

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
					if (wybrane_menu == 0) {
						menu.moveIt(-1);
					}
					else if (wybrane_menu == 1) {
						sterowanie.moveIt(-1);
					}
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					if (wybrane_menu == 0) {
						menu.moveIt(1);
					}
					else if (wybrane_menu == 1) {
						sterowanie.moveIt(1);
					}
				}
				if (wybrane_menu == 0)
				{//uruchamianie procedur na skutek wyboru menu (wybor poziomu menu to ENTER))
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						std::cout << "Uruchamiam gre..." << std::endl;
						wybrane_menu = 100;
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
					{
						std::cout << "Sterowanie" << std::endl;
						wybrane_menu = 1;
						sterowanie.pobierz_sterowanie(sterowanie.nowe_w, sterowanie.nowe_s, sterowanie.nowe_a, sterowanie.nowe_d);

					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
					{
						std::cout << "Koniec gry..." << std::endl;
						window.close();
					}
				}
				if (wybrane_menu == 1) {
					if (event.key.code == sf::Keyboard::Enter && sterowanie.getSelectedItem() == 0) {
						std::cin >> sterowanie.nowe_w;
					}
					if (event.key.code == sf::Keyboard::Enter && sterowanie.getSelectedItem() == 1) {
						std::cin >> sterowanie.nowe_s;
					}
					if (event.key.code == sf::Keyboard::Enter && sterowanie.getSelectedItem() == 2) {
						std::cin >> sterowanie.nowe_a;
					}
					if (event.key.code == sf::Keyboard::Enter && sterowanie.getSelectedItem() == 3) {
						std::cin >> sterowanie.nowe_d;
					}
					if (event.key.code == sf::Keyboard::Enter && sterowanie.getSelectedItem() == 4) {
						sterowanie.zmien_sterowanie(sterowanie.nowe_w, sterowanie.nowe_s, sterowanie.nowe_a, sterowanie.nowe_d);
						wybrane_menu = 0;
					}
				}
			}
		}


		if (wybrane_menu == 100) {
			gra.aktualizuj();
		}

		// wyczysc obszar rysowania
		window.clear(sf::Color::Magenta);
	
		// tutaj umiesc procedury rysujace...
		if (wybrane_menu == 0) {
			menu.draw(window);
		}
		if (wybrane_menu == 100) {
			sterowanie.pobierz_sterowanie(sterowanie.gora, sterowanie.dol, sterowanie.lewo, sterowanie.prawo);
			gra.rysuj(window);
		}
		if (wybrane_menu == 1) {
			sterowanie.draw(window);
		}


		// ostatnia czynnosc - wyswietl okno wraz zawartoscia
		window.display();
	}

	return 0;
}