#pragma once
#include "SFML/Graphics.hpp"
#include "display/ui.hpp"
#include <future>

/*

never set the ui mutex on any public methods. Those get sent from
the ui and will cause a deadlock if are blocked. 

*/


/*


+---------+---------+          +---------+---------+ 
|  logic  |  game   |          |   ui    | screen  | 
+---------+---------+          +---------+---------+ 
|        -->        |          |        <--        | 
|         |        ------------->        |         |
|         |         |          |         |         | 
|         |        <-------------        |         | 
|         |         |          |         |         | 
|         |         |          |         |         | 
|         |         |          |         |         | 
+---------+---------+          +---------+---------+ 










*/


namespace Game
{

class Game
{
public:
   Game();
   void mainLoop();
private:
   void displayLoop();
   void pollEvents();
   void closeWindow();
   void resizeWindow();
   void mouseMoved(sf::Vector2i mouse_pos);
   void mouseDown(sf::Vector2i mouse_pos);
   void mouseUp(sf::Vector2i mouse_pos);
   std::future<void> m_display_thread;
   mutable std::mutex m_ui_mutex;
   sf::RenderWindow m_window;
   Ui m_ui;
};

} // namespace Game
