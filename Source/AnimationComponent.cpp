#include "AnimationComponent.h"

//float AnimationComponent::Animation::time = 0.0f;

AnimationComponent::AnimationComponent(sf::Sprite* sprite, sf::Texture* sheet)
	: sprite(sprite)
	, sheet(sheet)
{
}

AnimationComponent::~AnimationComponent()
{
	std::cout << "Destructor " << __func__ << "\n";
}

void AnimationComponent::AddAnimation(std::string_view key, sf::Texture* sheet, float speed, int start_frame_x, int start_frame_y, int end_frame_x, int end_frame_y, int width, int height)
{
	animations[key.data()].Set(sprite, sheet, speed, start_frame_x, start_frame_y, end_frame_x, end_frame_y, width, height);
}

bool AnimationComponent::Play(std::string_view key, const float& frame_time, bool priority, float modifier, float modifier_max )
{

		if (last_animation != &animations[key.data()])
		{
			if (last_animation) {
				last_animation->Reset();
			}
		}
	

	animations[key.data()].Play(frame_time, modifier / modifier_max);
	last_animation = &animations[key.data()];

	return animations[key.data()].IsCompleted();
}

