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
	
	struct
	{
		Vector2 position = 0.0f,
			    size = 0.0f;
		Rect uvRect;
		MiUint color = 0xffffffff;

		std::unique_ptr<Texture> tex = nullptr;
	} Data;
private:
	void UpdateBounds();

	Font* m_font;
	Alignment am_lignment;
	Vector2 m_alignmentOffset;
	std::string m_text;
}
