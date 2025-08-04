#include "Font.h"

/// <summary>
/// Destroys the Font object and releases associated resources.
/// </summary>
piMath::Font::~Font()
{
	if (m_ttfFont != nullptr) {
		TTF_CloseFont(m_ttfFont);
	}
}

/// <summary>
/// Loads a font from a file with the specified name and size.
/// </summary>
/// <param name="name">The file path or name of the font to load.</param>
/// <param name="fontSize">The desired size of the font.</param>
/// <returns>True if the font was loaded successfully; false otherwise.</returns>
bool piMath::Font::Load(const std::string& name, float fontSize)
{

	m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
	if (m_ttfFont == nullptr) {
		std::cerr << "Could not load font: " << name << std::endl;
		return false;
	}

	return true;
}
