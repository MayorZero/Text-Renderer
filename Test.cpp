#include "Test.h"
#include "FontManager.h"

Test::Test(Renderer2D* renderer2D)
{
  renderer = renderer2D;
  
  FontManager::getInstance().Add(new Font("font", "font.ttf", 50);
  
  label = new Label("Test", {0.0f, 0.0f}, {0.0f, 0.0f}, "font", 0xff00ffff);
}

void Test::Draw()
{
  label->Draw(renderer);
}
