#include "pch.h"
#include "PauseState.h"

PauseState::PauseState(sf::RenderWindow* window, sf::Font& font)
	: font(font)
{
	background.setSize(
		sf::Vector2f(
			(float)window->getSize().x,
			(float)window->getSize().y
		)
	);

	background.setFillColor(sf::Color(10, 10, 10, 100));

	container.setSize(
		sf::Vector2f(
			(float)window->getSize().x / 4.0f,
			(float)window->getSize().y
		)
	);

	container.setFillColor(sf::Color(20, 20, 20, 200));

	container.setPosition(
		sf::Vector2f(
		(float)window->getSize().x / 2.0f - container.getSize().x / 2.0f,
			0.0f
		)
	);

	text.setFont(font);
	text.setCharacterSize(45);
	text.setFillColor(sf::Color(200,0,0,200));
	text.setString("P A U S E");
	text.setStyle(sf::Text::Style::Bold);
	text.setPosition(
		sf::Vector2f(
			(container.getPosition().x + container.getSize().x / 2.0f) - text.getGlobalBounds().width / 2.0f,
			50.0f
		)
	);
}

PauseState::~PauseState()
{
	std::cout << "Destructor " << __func__ << "\n";
}

bool PauseState::IsButtonPressed(std::string_view key)
{

	if (buttons.contains(key.data()))
		return buttons[key.data()].get()->IsPressed();
	else
		return false;
}

void PauseState::AddButton(std::string_view key,float rel_y, std::string_view text)
{
	buttons[key.data()] = make_unique<gui::Button>(
		(container.getPosition().x + container.getSize().x / 2.0f) - this->text.getGlobalBounds().width / 2.0f, 
		50.0f + rel_y,
		150,
		50,
		text.data(),
		&font
		);
}

void PauseState::Update(sf::Vector2f mos_pos, const float& frame_time)
{
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->Update(mos_pos, frame_time);
	}
}

void PauseState::Render(sf::RenderWindow* target)
{

	target->draw(background);
	target->draw(container);
	target->draw(text);

	for (auto it = buttons.begin(); it!= buttons.end(); it++)
	{
		it->second->Render(target);
	}






	container.setSize(
		sf::Vector2f(
		(float)target->getSize().x / 4.0f,
			(float)target->getSize().y
		)
	);

	container.setPosition(
		sf::Vector2f(
		(float)target->getSize().x / 2.0f - container.getSize().x / 2.0f,
			0.0f
		)
	);

	text.setPosition(
		sf::Vector2f(
		(container.getPosition().x + container.getSize().x / 2.0f) - text.getGlobalBounds().width / 2.0f,
			50.0f
		)
	);

	buttons["Resume"]->SetPosition(
		(container.getPosition().x + container.getSize().x / 2.0f) - this->text.getGlobalBounds().width / 2.0f,
		target->getSize().y * 0.35f
	);

	buttons["Options"]->SetPosition(
		(container.getPosition().x + container.getSize().x / 2.0f) - this->text.getGlobalBounds().width / 2.0f,
		target->getSize().y * 0.45f
	);

	buttons["Quit"]->SetPosition(
		(container.getPosition().x + container.getSize().x / 2.0f) - this->text.getGlobalBounds().width / 2.0f,
		target->getSize().y * 0.75f
	);
}
