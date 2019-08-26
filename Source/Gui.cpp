#include "Gui.h"


sf::Clock gui::Button::clock;

namespace gui
{
	Button::Button(float x, float y, float widht, float height,
		string text, sf::Font* font, int character_size,
		sf::Color idle_text_color, sf::Color hover_text_color, sf::Color active_text_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
	{
		shape.setSize(sf::Vector2f(widht, height));
		shape.setPosition(sf::Vector2f(x, y));

		this->font = font;
		this->text.setFont(*(this->font));
		this->text.setString(text);
		this->text.setFillColor(sf::Color::White);
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
			if (clock.getElapsedTime().asSeconds() >= 30.f * frame_time)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					STATE = STATES::BTN_PRESSED;
					clock.restart();
				}
			}
		}


		switch (STATE)
		{
		case Button::STATES::BTN_IDLE:
			shape.setFillColor(idle_color);
			text.setFillColor(idle_text_color);
			break;

		case Button::STATES::BTN_PRESSED:
			shape.setFillColor(pressed_color);
			text.setFillColor(pressed_text_color);
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



	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ///
	//  //////												DROP																	    //////  //
	//  //////													LIST																    //////  //
	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// ///

	DropList::DropList(float pos_x, float pos_y, float width, float height, sf::Font& font, std::vector<std::string> list, unsigned int default_index)
		:  font(font)
	{
		for (size_t i = 0; i <list.size(); i++)
		{
			this->list.push_back(
				std::make_unique<Button>(
					pos_x, 
					pos_y + (i+1)*height,
					width, 
					height, 
					list[i], 
					&font,
					13,
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
			13,
			sf::Color(75, 75, 75, 255),
			sf::Color(145, 145, 145, 255),
			sf::Color(150, 0, 0, 255),
			sf::Color(75, 75, 75, 100),
			sf::Color(145, 145, 145, 100),
			sf::Color(150, 0, 0, 100)
			);

		active_element->text.setString( this->list[default_index].get()->text.getString() );
		active_element->SetPosition(pos_x, pos_y);
	
	}

	DropList::~DropList()
	{
		std::cout << "Destructor " << __func__ << "\n";
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
					active_element->text.setString(el.get()->text.getString());
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
	}
}

