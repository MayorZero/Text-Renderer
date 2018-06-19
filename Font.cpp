#include "Font.h"

Font::Font(const std::string& name, const std::string& filename, float size)
  : m_name(name), m_filename(filename), m_size(size), m_texture(nullptr)
{
  m_FTAtlas = ftgl::texture_atlas_new(512, 512, 1); // tried with depth 2 too
  m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, m_size, filename.c_str());

  TextureParameters parameters = { TextureFormat::ALPHA, TextureFilter::LINEAR, TextureFilter::LINEAR, TextureWrap::CLAMP_TO_EDGE };
  m_texture = m_texture->Create(512, 512, parameters);
  m_texture->setData(m_FTAtlas->data);
}

Texture* Font::getTexture() const
{
  UpdateAtlas();
  return m_texture;
}

void Font::UpdateAtlas() const
{
  m_texture->setData(FTAtlas->data);
}
