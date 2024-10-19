#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "menu.hpp"
using namespace sf;

int main()
{

  RenderWindow window(VideoMode(1920, 1080), "Main Menu", Style::Default);
  Menu menu(window.getSize().x, window.getSize().y);
  menu.initializeMenu(window);
	menu.menuWrapper();

	return 0;
}
