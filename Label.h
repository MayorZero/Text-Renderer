class Label
{
public:
	Label(const std::string& text, float x, float y, const std::string& font, Uint color);

	void Draw(Renderer2D* renderer) const;

	void SetText(const std::string& text);

	inline const Font& getFont() const { return *m_font; }
	inline const std::string& getText() const { return m_text; }
private:
	void UpdateBounds();

	Font* m_font;
	std::string m_text;
