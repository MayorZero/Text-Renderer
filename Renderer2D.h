enum
{
	MAX_SPRITES = 60000,
  MAX_ELEMENTS = MAX_SPRITES * 6,
  MAX_TEXTURES = 32 - 1,
  SPRITE_SIZE = sizeof(Vertex) * 4,
};

enum BUFFER_SIZE
{
  VERTEX = SPRITE_SIZE * MAX_SPRITES,
  ELEMENT = MAX_ELEMENTS * sizeof(GLuint),
};

enum SHADER_OUT
{
  POSITION = 0,
  COLOR = 1,
  UV = 2,
  TEXTURE = 3
};

class Renderer2D
{
public:
  Renderer2D() = default;
  ~Renderer2D();

  void Create(Window* window);
  
  void Begin();
  void DrawString(const std::string& text, const Vector2& position, Uint color = 0xffffffff, const Font& font = *FontManager::getInstance().Get());
  void Present();

private:
  std::unique_ptr<API::VertexArray> m_vao = nullptr;
  std::unique_ptr<API::Buffer> m_vbo = nullptr,
                               m_ebo = nullptr;

  std::vector<Texture*> m_texture;

  Uint m_indexCount = 0;
  Vertex* m_buffer = nullptr;

  Camera2D m_camera;

  Uint* setIndices();
  void End();
  float SummitTexture(Texture* texture);
};
