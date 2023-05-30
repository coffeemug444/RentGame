#pragma once
#include <SFML/Graphics.hpp>
#include "display/buttons/buttonContainer.hpp"

namespace Game
{

class Screen;

class Widget : public ButtonContainer
{
public:
   Widget(const std::vector<Button*>& buttons = {}, const std::vector<ButtonContainer*>& sub_containers = {});
   void handleClick(int button_id) override {};
};



} // namespace Game
