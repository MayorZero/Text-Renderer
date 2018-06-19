std::vector<std::unique_ptr<Font>> FontManager::m_font;

FontManager::~FontManager()
{
	Free();
}

FontManager& FontManager::getInstance()
{
	static FontManager instance;
	return instance;
}

void FontManager::Add(Font* font)
{
	m_font.push_back(std::unique_ptr<Font>(font));
}

Font* FontManager::Get()
{
	return m_font[0].get();
}

Font* FontManager::Get(const std::string& name)
{
	for (const auto& font : m_font) {
		if (font->getName() == name) {
			return font.get();
		}
	}

	return nullptr;
}

Font* FontManager::Get(Uint size)
{
	for (const auto& font : m_font) {
		if (font->getFontSize() == size) {
			return font.get();
		}
	}

	return nullptr;
}

Font* FontManager::Get(const std::string& name, Uint size)
{
	for (const auto& font : m_font) {
		if (font->getFontSize() == size && font->getName() == name) {
			return font.get();
		}
	}
	return nullptr;
}

void FontManager::Free()
{
	m_font.clear();
}
