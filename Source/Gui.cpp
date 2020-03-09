#include "pch.h"
#include "Gui.h"

sf::Clock gui::Button::clock;

namespace gui
{
	Button::Button(	float x, 
					float y, 
					float widht,
					float height,
					string text,
					sf::Font* font,
					int character_size,
					sf::Color idle_text_color, 
					sf::Color hover_text_color, 
					sf::Color active_text_color,
					sf::Color idle_color, 
					sf::Color hover_color,
					sf::Color active_color)
	{
		shape.setFillColor(idle_color);
		shape.setSize(sf::Vector2f(widht, height));
		shape.setPosition(sf::Vector2f(x, y));

		this->font = font;
		this->text.setFont(*(this->font));
		this->text.setString(text);
		this->text.setFillColor(idle_text_color);
		this->text.setCharacterSize(character_size);
		this->text.setStyle(sf::Text::Bold);

		this->text.setPosition(
			this->shape.getPosition().x + shape.getGlobalBounds().width / 2.0f - this->text.getGlobalBounds().width / 2.0f,
			this->shape.getPosition().y + shape.getGlobalBounds().height / 2.0f - this->text.getGlobalBounds().height / 2.0f - 3 // -3 for precision
		);


		this->idle_color = idle_color;
		this->hover_color = hover_color;
		this->pressed_color = active_color;

		this->idle_text_color = idle_text_color;
		this->hover_text_color = hover_text_color;
		this->pressed_text_color = active_text_color;


	}

	Button::~Button()
	{
		std::cout << "Destructor " << __func__ << " " << static_cast<string>(text.getString()) << "\n";
	}

	void Button::Update(sf::Vector2f mouse_pos, const float& frame_time)
	{
		STATE = STATES::BTN_IDLE;
		if (shape.getGlobalBounds().contains(mouse_pos))
		{
			STATE = STATES::BTN_HOVER;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// 20.f good work for 60 fps
				if (clock.getElapsedTime().asSeconds() >= 20.f * frame_time)
				{

					STATE = STATES::BTN_PRESSED;
					clock.restart();

				}
				clock.restart();
			}
		}


		switch (STATE)
		{
		case Button::STATES::BTN_IDLE:
			shape.setFillColor(idle_color);
			text.setFillColor(idle_text_color);
			break;

		case Button::STATES::BTN_PRESSED:
			//shape.setFillColor(pressed_color);
			//text.setFillColor(pressed_text_color);
			break;

		case Button::STATES::BTN_HOVER:
			shape.setFillColor(hover_color);
			text.setFillColor(hover_text_color);
			break;

		default:
			break;
		}

	}

	void Button::Render(sf::RenderWindow* window)
	{
		window->draw(shape);
		window->draw(text);
	}

	void Button::SetPosition(float x, float y)
	{
		shape.setPosition(sf::Vector2f(x, y));
		this->text.setPosition(
			this->shape.getPosition().x + shape.getGlobalBounds().width / 2.0f - this->text.getGlobalBounds().width / 2.0f,
			this->shape.getPosition().y + shape.getGlobalBounds().height / 2.0f - this->text.getGlobalBounds().height / 2.0f - 3 // -3 for precision
		);
	}

	void Button::SetScale(float x, float y)
	{
		shape.setScale(x, y);
		text.setScale(x, y);

	}

	void Button::SetSizeShape(float x, float y)
	{
		shape.setSize(sf::Vector2f(x, y));
	}

	void Button::SetTextScale(float x, float y)
	{
		text.setScale(x, y);
	}

	sf::Vector2f Button::GetPosition() const
	{
		return sf::Vector2f(shape.getPosition());
	}

	sf::Vector2f Button::GetSize() const
	{
		return sf::Vector2f(shape.getSize());
	}




	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ///
	//  //////												DROP																	    //////  //
	//  //////													LIST																    //////  //
	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ///

	DropList::DropList(float pos_x, float pos_y, float width, float height, sf::Font& font, std::vector<string> list, string text, unsigned int default_index)
		:  font(font)
	{
		int i = 1;
		for (const auto& el: list)
		{
			this->list.push_back(
				std::make_unique<Button>(
					pos_x, 
					pos_y + (i++)*height,
					width, 
					height, 
					el, 
					&font,
					15,
					sf::Color(75, 75, 75, 255),
					sf::Color(145, 145, 145, 255),
					sf::Color(150, 0, 0, 255),
					sf::Color(75, 75, 75, 100),
					sf::Color(145, 145, 145, 100),
					sf::Color(150, 0, 0, 100)
					)
			);
		}

		active_element = std::make_unique<Button>(
			pos_x,
			pos_y,
			width,
			height,
			" ",
			&font,
			15,
			sf::Color(75, 75, 75, 255),
			sf::Color(145, 145, 145, 255),
			sf::Color(150, 0, 0, 255),
			sf::Color(25, 75, 75, 100),
			sf::Color(145, 145, 145, 100),
			sf::Color(150, 0, 0, 100)
			);
	
		this->text.setString(text);
		this->text.setPosition(pos_x - text.length() * 7, pos_y + 13);
		this->text.setFont(font);
		this->text.setCharacterSize(15);
		this->text.setStyle(sf::Text::Bold);

		if (!list.empty())
		{
			active_element->text.setString(this->list[default_index]->text.getString());
		}

		active_element->SetPosition(pos_x, pos_y);
	
	}

	DropList::~DropList()
	{
		std::cout << "Destructor " << __func__ <<" "<< text.getString().toAnsiString()<< " \n";
	}
	void DropList::Update(sf::Vector2f mouse_pos, const float& frame_time)
	{

		if (bShowList)
		{
			for (const auto& el : list)
			{
				el->Update(mouse_pos, frame_time);
				if (el->IsPressed())
				{
					bShowList = !bShowList; //NICE
					active_element->text.setString(el->text.getString());
				}
			}
		}
	
		if (active_element) 
			active_element->Update(mouse_pos, frame_time);

		if (active_element && active_element->IsPressed()){ 
			bShowList = !bShowList; //NICE
		}
		

	}
	void DropList::Render(sf::RenderWindow* window)
	{
		if (bShowList)
		{
			for (const auto& el : list) {
				el->Render(window);
			}
		}

		if (active_element)
			active_element->Render(window);

		window->draw(text);
	}


	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ///
	//  //////												TEXTURE																	    //////  //
	//  //////													SELECTOR															    //////  //
	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ///
	TextureSelector::TextureSelector(float x, float y, float width, float height, float grid_size)
		: active(false)
		, hidden(false)
	{
		font_dosis.loadFromFile("Data/Fonts/Dosis-Light.ttf");

		hide_button = std::make_unique<Button>(x+10, height*1.05, 50, 50, "HideTab", &font_dosis, 25, sf::Color(255, 0, 0, 255) );

		bounds.setSize(sf::Vector2f(width, height));
		bounds.setPosition(x, y);
		bounds.setFillColor(sf::Color(50, 50, 50, 100));
		bounds.setOutlineColor(sf::Color(250, 250, 250, 200));
		bounds.setOutlineThickness(1);

		texture_sheet.setPosition(x, y);

		this->grid_size = grid_size;

		selector.setPosition(x, y);
		selector.setSize(sf::Vector2f(grid_size, grid_size));
		selector.setFillColor(sf::Color::Transparent);
		selector.setOutlineColor(sf::Color::Red);
		selector.setOutlineThickness(2);
	}
	void TextureSelector::Update(const float& frame_time, const sf::Vector2f mouse_pos_window)
	{
		hide_button->Update(mouse_pos_window, frame_time);
		if (hide_button->IsPressed())
			hidden = !hidden;

		if (bounds.getGlobalBounds().contains(mouse_pos_window) && !hidden)
			active = true;
		else
			active = false;

		if (active)
		{
			// Oblicz dlugoœæ a póŸniej podziel aby sprawdziæ który to kafelek
			mouse_pos.x = (mouse_pos_window.x - (int)bounds.getPosition().x ) / (unsigned)grid_size;
			mouse_pos.y = (mouse_pos_window.y - (int)bounds.getPosition().y ) / (unsigned)grid_size;
			
			// Przesuñ od pocz¹tku o odpowiedni¹ dlugoœæ (w pikselach) w osi X i Y
			selector.setPosition(
				bounds.getPosition().x + (mouse_pos.x * grid_size),
				bounds.getPosition().y + (mouse_pos.y * grid_size)
			);

				texture_rect.width  = 100;
				texture_rect.height = 100;
				texture_rect.left  = (selector.getPosition().x - bounds.getPosition().x) ;
				texture_rect.top   = (selector.getPosition().y - bounds.getPosition().y) ;
		}
		

	}

	void TextureSelector::Render(sf::RenderWindow* window)
	{
		if (window)
		{
			if (!hidden)
			{
				window->draw(bounds);
				window->draw(texture_sheet);
				if (active)
				{
					window->draw(selector);
				}
			}
			else
			{

			}
			hide_button->Render(window);
		}
	}

	void TextureSelector::SetTexture(sf::Texture* texture)
	{
		texture_sheet.setTexture(*texture);
		if (texture_sheet.getGlobalBounds().width > bounds.getGlobalBounds().width)
		{
			texture_sheet.setTextureRect(sf::IntRect(
				0,
				0,
				bounds.getGlobalBounds().width,
				texture_sheet.getGlobalBounds().height
			));
		}

		if (texture_sheet.getGlobalBounds().height > bounds.getGlobalBounds().height)
		{
			texture_sheet.setTextureRect(sf::IntRect(
				0,
				0,
				texture_sheet.getGlobalBounds().width,
				bounds.getGlobalBounds().height
			));
		}
	}
}

