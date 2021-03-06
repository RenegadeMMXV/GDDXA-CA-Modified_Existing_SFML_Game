/**
*	@author			[NAME]
*	@creationDate	XXXX/XX/XX	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>

#include <SFML\Graphics.hpp>

namespace GUI {
	namespace ButtonStyle {
		enum {
			NONE = 0,
			SAVE = 1,
			CANCEL = 2,
			CLEAN = 3,
		};
	};

	namespace ButtonState {
		enum {
			NORMAL = 0,
			HOVERED = 1,
			CLICKED = 2
		};
	};

	class Button : public sf::Drawable {
	public:
		Button();
		Button(std::string s, sf::Font& font, sf::Vector2f position, sf::Uint32 ButtonStyle);

		~Button();

		void setColourTextNormal(sf::Color text) { m_textNormal = text; };
		void setColourTextHover(sf::Color text) { m_textHover = text; };
		void setColourTextClicked(sf::Color text) { m_textClicked = text; };
		void setColourNormal(sf::Color bgNormal) { m_bgNormal = bgNormal; };
		void setColourHover(sf::Color bgHover) { m_bgHover = bgHover; };
		void setColourClicked(sf::Color bgClicked) { m_bgClicked = bgClicked; };
		void setBorderColour(sf::Color border) { m_border = border; };
		void setBorderThickness(float t) { m_borderThickness = t; };
		void setBorderRadius(float r) { m_borderRadius = r; };
		void setPosition(sf::Vector2f position) { m_position = position; };
		void setSize(unsigned int size);
		
		void setText(std::string s);
		void setStyle(sf::Uint32 ButtonStyle);
		void setFont(sf::Font& font);

		sf::Vector2f getPosition() { return m_position; };
		sf::Vector2f getDimensions() { return sf::Vector2f(m_button.getGlobalBounds().width, m_button.getGlobalBounds().height); };
		sf::Uint32 getState() { return m_btnstate; };

		void update(sf::Event& e, sf::Time t, sf::RenderWindow& window);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
		sf::Color m_bgNormal;
		sf::Color m_bgHover;
		sf::Color m_bgClicked;
		sf::Color m_textNormal;
		sf::Color m_textHover;
		sf::Color m_textClicked;
		sf::Color m_border;

		float m_borderThickness;
		float m_borderRadius;
		sf::Vector2f m_size;
		sf::Vector2f m_position;
		sf::Uint32 m_style;
		sf::Uint32 m_btnstate;

		sf::RectangleShape m_button;
		sf::Font m_font;
		unsigned int m_fontSize;
		sf::Text m_text;
		sf::Text m_shadow;

		sf::Time m_sinceLastClick;
	};
};

#endif // !BUTTON_H
