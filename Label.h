class Label
{
public:
	enum class Alignment
	{
		NONE = 0, LEFT, CENTER, RIGHT
	};

	Label(const std::string& text, float x, float y, const std::string& font, Uint color, Alignment alignment = Alignment::LEFT);
	void Draw(Renderer2D* renderer) const;
	void SetAlignment(Alignment alignment);
	void SetText(const std::string& text);

	inline const Font& getFont() const { return *m_font; }
	inline Alignment getAlignment() const { return m_alignment; }
	inline const std::string& getText() const { return m_text; }
private:
	void UpdateBounds();

	Font* m_font;
	Alignment am_lignment;
	Vector2 m_alignmentOffset;
	std::string m_text;
}
