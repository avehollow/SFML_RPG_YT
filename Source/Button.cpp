#include "Button.h"

Button::Button(float x, float y, float widht, float height, string text, sf::Font* font, sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	shape.setSize(sf::Vector2f(widht, height));
	shape.setPosition(sf::Vector2f(x, y));

	this->font = font;
	this->text.setFont( *(this->font) );
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(15);

	this->text.setPosition(
		this->shape.getPosition().x + shape.getGlobalBounds().width / 2.0f - this->text.getGlobalBounds().width  / 2.0f ,
		this->shape.getPosition().y + shape.getGlobalBounds().height / 2.0f - this->text.getGlobalBounds().height / 2.0f
	);


	this->idle_color   = idle_color;
	this->hover_color  = hover_color;
	this->pressed_color = active_color;


}

Button::~Button()
{
	std::cout << "Destructor " << __func__ << "\n";
}

void Button::Update(sf::Vector2f mouse_pos)
{
	STATE = STATES::BTN_IDLE;

	if (shape.getGlobalBounds().contains(mouse_pos))
	{
		STATE = STATES::BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			STATE = STATES::BTN_PRESSED;
		}
	}
		
	switch (STATE)
	{
	case Button::STATES::BTN_IDLE:
		shape.setFillColor(idle_color);
		break;

	case Button::STATES::BTN_PRESSED:
		shape.setFillColor(pressed_color);
		break;

	case Button::STATES::BTN_HOVER:
		shape.setFillColor(hover_color);
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

