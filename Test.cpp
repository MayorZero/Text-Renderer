#include "Test.h"
#include "FontManager.h"

Test::Test(Renderer2D* renderer2D)
{
  m_renderer = renderer2D;
  
  FontManager::getInstance().Add(new Font("font", "font.ttf", 50);
  
  m_label = new Label("Test", 0.0f, 0.0f, "font", 0xff00ffff);
}

void Test::Draw()
{
  m_label->Draw(m_renderer);
}
