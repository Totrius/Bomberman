#include "menu.h"
#include "Gra.h"
#include "Bomba.h"

//#define TEST

int main()
{
#ifdef TEST
	postac();
	return 0;
#endif
	int wybrane_menu = 0;

	sf::Music music;
	if (!music.openFromFile("menu_theme.ogg"))
		return -1; // error
	music.setLoop(true);
	/*music.play();*/

	//Rysuj grê
	wybrane_menu = 100;

	sf::RenderWindow window(sf::VideoMode(1000, 800), "My Bombeer");// utworz okno

	Menu menu(window.getSize().x, window.getSize().y);
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
					menu.moveIt(-1);
				}

				if (event.key.code == sf::Keyboard::Down)
				{
					menu.moveIt(1);
				}
				if (wybrane_menu == 0)
				{//uruchamianie procedur na skutek wyboru menu (wybor poziomu menu to ENTER))
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						std::cout << "Uruchamiam gre..." << std::endl;
						wybrane_menu = 1;
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
					{
						std::cout << "Najlepsze wyniki..." << std::endl;
						wybrane_menu = 1;
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
					{
						std::cout << "Koniec gry..." << std::endl;
						window.close();
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
			gra.rysuj(window);
		}


		// ostatnia czynnosc - wyswietl okno wraz zawartoscia
		window.display();
	}

	return 0;
}