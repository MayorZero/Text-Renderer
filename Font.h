class Font
{

public:
  Font(const std::string& name, const std::string& filename, float size);

  inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }
  inline const std::string& getName() const { return m_name; }
  inline const std::string& getFileName() const { return m_filename; }
  inline float getFontSize() const { return m_size; }

  Vector2 getOffsets(const std::string& text) const;
  float getWidth(const std::string& text) const;
  float getHeight(const std::string& text) const;
  Vector2 getSize(const std::string& text) const;

  Rect getBounds(const std::string& text) const;

  Texture* getTexture() const;

  inline Uint getID() const { return m_FTAtlas->id; }

private:
  void UpdateAtlas() const;

  ftgl::texture_atlas_t* m_FTAtlas = nullptr;
  ftgl::texture_font_t* m_FTFont = nullptr;

  float m_size;
  std::string m_name;
  std::string m_filename;
  mutable Texture* m_texture = nullptr;
};
