#include "Button.h"

Button::Button(float x, float y, float widht, float height,
	string text, sf::Font* font,
	sf::Color idle_text_color, sf::Color hover_text_color, sf::Color active_text_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	shape.setSize(sf::Vector2f(widht, height));
	shape.setPosition(sf::Vector2f(x, y));

	this->font = font;
	this->text.setFont( *(this->font) );
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(35);
	this->text.setStyle(sf::Text::Bold);

	this->text.setPosition(
		this->shape.getPosition().x + shape.getGlobalBounds().width  / 2.0f - this->text.getGlobalBounds().width  / 2.0f ,
		this->shape.getPosition().y + shape.getGlobalBounds().height / 2.0f - this->text.getGlobalBounds().height / 2.0f - 3 // -3 for precision
	);


	this->idle_color    = idle_color;
	this->hover_color   = hover_color;
	this->pressed_color = active_color;

	this->idle_text_color    = idle_text_color;
	this->hover_text_color   = hover_text_color;
	this->pressed_text_color = active_text_color;


}

Button::~Button()
{
	std::cout << "Destructor " << __func__ <<" "<< static_cast<string>(text.getString()) <<  "\n";
}

void Button::Update(sf::Vector2f mouse_pos, const float& frame_time)
{
	STATE = STATES::BTN_IDLE;
	if (clock.getElapsedTime().asSeconds() >= 0.1f * frame_time)
	{
		if (shape.getGlobalBounds().contains(mouse_pos))
		{
			STATE = STATES::BTN_HOVER;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				STATE = STATES::BTN_PRESSED;
			}
		}
		clock.restart();
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

