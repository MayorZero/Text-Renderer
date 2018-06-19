Label::Label(const std::string& text, float x, float y, const std::string& font, Uint color, Alignment alignment)
  : font(FontManager::getInstance().Get(font))
{
  Data.position = { x, y };
  SetText(text);
  SetAlignment(alignment);
  Data.color = color;

  ValidateFont(font);
}

void Label::Draw(Renderer2D* renderer) const
{
  renderer->DrawString(text, Data.position - Data.size + alignmentOffset, Data.color, *font);
}

void Label::SetAlignment(Alignment alignment)
{
  m_alignment = alignment;
  UpdateBounds();
}

void Label::SetText(const std::string& t)
{
  text = t;
  UpdateBounds();
}

void Label::UpdateBounds()
{
  Vector2 size = font->getSize(text) * 0.5f;
  Data.size = size;
  switch (alignment) {
    case Alignment::LEFT: alignmentOffset.x = size.x; break;
    case Alignment::CENTER: alignmentOffset.x = 0.0f; break;
    case Alignment::RIGHT: alignmentOffset.x = -size.x; break;
  }
}
