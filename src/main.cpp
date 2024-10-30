#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "menu.hpp"

/* TO DO:
 * Can't see hp and stamina bar
 * Generator at escape ship says generator fixed?
 * After the game has ended, menu doesn't print out menu titles?
 * During game loop, user can press esc
 */
int main()
{

  //intialize main menu of this window
  Menu menu;
	menu.menuWrapper();

	return 0;
}
