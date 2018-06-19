class FontManager
{
public:
  ~FontManager();
  static FontManager& getInstance();

  void Add(Font* font);
  Font* Get();
  Font* Get(const std::string& name);
  Font* Get(Uint size);
  Font* Get(const std::string& name, Uint size);
  void Free();

private:
  FontManager() {}

  static std::vector<std::unique_ptr<Font>> m_font;
};
