#pragma once

// HACK IMPORTANT Calculate gui item position based on the window size. LIKE Unreal engine 4 ANCHORS!!!
//		  window->getSize().x * 0.4f
//		  window->getSize().y * 0.7f

//This pointer does not manage memory; Dont try to delete ! This pointer used only for access to data
#define ACCESS_POINTER 

using std::string;
namespace gui
{

	class Button
	{
		enum class STATES : uint8_t
		{
			BTN_IDLE = 0,
			BTN_PRESSED = 1,
			BTN_HOVER = 2
		};


		static sf::Clock clock;
		sf::RectangleShape shape;

		STATES    STATE = STATES::BTN_IDLE;

	public:
		sf::Text  text;
		sf::Font* font = nullptr;

		sf::Color idle_color;
		sf::Color hover_color;
		sf::Color pressed_color;

		sf::Color idle_text_color;
		sf::Color hover_text_color;
		sf::Color pressed_text_color;


		Button(
			float x,
			float y,
			float widht,
			float height,
			string  text,
			sf::Font* font,
			int character_size = 35,
			sf::Color idle_text_color    = sf::Color(75, 75, 75, 255),		    //dark  grey
			sf::Color hover_text_color   = sf::Color(145, 145, 145, 255),       //light grey
			sf::Color active_text_color  = sf::Color(150, 0, 0, 255),	        //dark  red
			sf::Color idle_color         = sf::Color(75, 75, 75, 0),		 //dark  grey
			sf::Color hover_color        = sf::Color(145, 145, 145, 0),		 //light grey
			sf::Color active_color       = sf::Color(150, 0, 0, 0)			 //dark  red
		);

		virtual ~Button();

		void Update(sf::Vector2f mouse_pos, const float& frame_time);
		void Render(sf::RenderWindow* window);


		const bool IsPressed() const {
			return STATE == STATES::BTN_PRESSED ? true : false;
		}

		const bool IsHovered() const {
			return STATE == STATES::BTN_HOVER ? true : false;
		}

		const bool IsIdle() const {
			return STATE == STATES::BTN_IDLE ? true : false;
		}

		void SetPosition(float x, float y);
		sf::Vector2f GetPosition()const;
	};

	class DropList
	{
	private:
		std::unique_ptr<Button> active_element;
		std::vector<std::unique_ptr<Button>> list;
		sf::Text text;

		sf::Font& font;

		bool bShowList = false;

	public:
		DropList(float pos_x, float pos_y, float width, float height, sf::Font& font, std::vector<string> list, string text, unsigned int default_index = 0 );
		virtual ~DropList();

		void Update(sf::Vector2f mouse_pos, const float& frame_time);
		void Render(sf::RenderWindow* window);

		// HACK lower copy
		Button* GetActiveElement()
		{
			return active_element.get();
		};
	};

	class TextureSelector
	{
	private:
		sf::RectangleShape bounds;
		sf::Sprite texture_sheet;

		sf::RectangleShape selector;
		sf::Vector2u mouse_pos;

		float grid_size;

		sf::Font font_dosis;
		bool hidden;
		std::unique_ptr<Button> hide_button;
	public:
		sf::IntRect texture_rect;
		bool active;

	public:
		TextureSelector(float x, float y, float width, float height, float grid_size);
		~TextureSelector() = default;

		void Update(const float& frame_time, const sf::Vector2f mouse_pos_window);
		void Render(sf::RenderWindow* window);

		void SetTexture(sf::Texture* texture);
	};


}

