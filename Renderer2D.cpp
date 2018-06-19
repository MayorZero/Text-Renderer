#include "Renderer2D.h"

Renderer2D::~Renderer2D()
{
  m_vao->Free();
  m_vbo->Free();
  m_ebo->Free();

  for (const auto& texture : m_texture) {
    delete texture;
  }
  m_texture.clear();
}

void Renderer2D::Create(Window* window)
{
  int w = 0,
      h = 0;
  window->getWindowSize(&w, &h);
  m_camera.Projection(0.0f, (float)w, 0.0f, (float)h);

  m_vao = std::unique_ptr<API::VertexArray>(m_vao->Create());
  m_vbo = std::unique_ptr<API::Buffer>(m_vbo->Create(API::BUFFER::ARRAY, API::DRAW::DYNAMIC));
  m_ebo = std::unique_ptr<API::Buffer>(m_ebo->Create(API::BUFFER::ELEMENT, API::DRAW::STATIC));

  m_vbo->AddData(BUFFER_SIZE::VERTEX, nullptr);
  m_ebo->AddData(BUFFER_SIZE::ELEMENT, setIndices());

  m_vbo->AddAttribute(SHADER_OUT::POSITION, 2, GL_FLOAT,         GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
  m_vbo->AddAttribute(SHADER_OUT::COLOR,    4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(Vertex), (const void*)offsetof(Vertex, color));
  m_vbo->AddAttribute(SHADER_OUT::UV,       2, GL_FLOAT,         GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, uv));
  m_vbo->AddAttribute(SHADER_OUT::TEXTURE,  1, GL_FLOAT,         GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texID));

  m_vao->UnbindVertexArray();
}

void Renderer2D::Begin()
{
  glm::mat4 cameraMatrix = glm::mat4(1.0f);
  cameraMatrix = camera.getCameraMatrix();
  glUniformMatrix4fv(1, 1, GL_FALSE, &(cameraMatrix[0][0]));

  camera.Update();
  mappedVertex = vbo->getDataPointer<Vertex>();
}

void Renderer2D::DrawString(const std::string& text, const Vector2& position, Uint color, const Font& font)
{
  Texture* texture = font.getTexture();
  float textureSlot = FindTexture(texture);

  const Vector2& scale = 1.0f;// font.getScale();

  float x = position.x;

  texture_font_t* ftFont = font.getFTFont();

  for (Uint i = 0; i < text.length(); i++) {
    texture_glyph_t* glyph = texture_font_get_glyph(ftFont, text.c_str());
    if (glyph) {
      if (i > 0) {
        float kerning = texture_glyph_get_kerning(glyph, text.c_str() + i - 1);
        x += kerning / scale.x;
      }

      float x0 = x + glyph->offset_x / scale.x;
      float y0 = position.y + glyph->offset_y / scale.y;
      float x1 = x0 + glyph->width / scale.x;
      float y1 = y0 - glyph->height / scale.y;

      float u0 = glyph->s0;
      float v0 = glyph->t0;
      float u1 = glyph->s1;
      float v1 = glyph->t1;

      m_buffer->position = Vector3(x0, y0, 0);
      m_buffer->uv = Vector2(u0, v0);
      m_buffer->texID = textureSlot;
      m_buffer->color = color;
      m_buffer++;

      m_buffer->position = Vector3(x0, y1, 0);
      m_buffer->uv = Vector2(u0, v1);
      m_buffer->texID = textureSlot;
      m_buffer->color = color;
      m_buffer++;

      m_buffer->position = Vector3(x1, y1, 0);
      m_buffer->uv = Vector2(u1, v1);
      m_buffer->texID = textureSlot;
      m_buffer->color = color;
      m_buffer++;

      m_buffer->position = Vector3(x1, y0, 0);
      m_buffer->uv = Vector2(u1, v0);
      m_buffer->texID = textureSlot;
      m_buffer->color = color;
      m_buffer++;

      m_indexCount += 6;

      x += glyph->advance_x;
    }
  }
}

void Renderer2D::End()
{
  vbo->releaseDataPointer();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer2D::Present()
{
  End();

  for (Uint i = 0; i < m_texture.size(); ++i) {
   m_texture[i]->BindTexture(i);
  }

  m_vao->BindVertexArray();
  m_vao->DrawElements(API::ELEMENTS, indexCount);
  m_vao->UnbindVertexArray();

  for (Uint i = 0; i < m_texture.size(); ++i) {
    m_texture[i]->UnbindTexture(i);
  }

  m_indexCount = 0;
  m_texture.clear();

  glDisable(GL_BLEND);
}

Uint* Renderer2D::setIndices()
{
  Uint* indices = new MiUint[BUFFER_SIZE::ELEMENT],
        offset = 0;
  for (int i = 0; i < BUFFER_SIZE::ELEMENT; i += 6) {
    indices[i] = offset;
    indices[i + 1] = offset + 1;
    indices[i + 2] = offset + 2;
    indices[i + 3] = offset + 2;
    indices[i + 4] = offset + 3;
    indices[i + 5] = offset;

    offset += 4;
  }

  return indices;
}

float Renderer2D::SummitTexture(Texture* t)
{
  float result = 0.0f;
  bool found = false;
  for (Uint i = 0; i < m_texture.size(); ++i) {
    if (m_texture[i] == t) {
      result = (float)(i + 1);
      found = true;
      break;
    }
  }

  if (!found) {
    if (m_texture.size() >= MAX_TEXTURES) {
      Render();
      RenderClear();
    }
    m_texture.push_back(t);
    result = (float)(m_texture.size());
  }

  return result;
}
