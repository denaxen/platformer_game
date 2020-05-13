#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "skeleton.h"

class Skeleton;

class SkeletonState
{
protected:
	Animation animation;
public:
	SkeletonState();

	sf::Vector2i get_size();
	void set_sprite(sf::Sprite& sprite, bool is_faced_right);

	virtual void handle_events(Skeleton* skeleton, const sf::Event& event);
	virtual void update(Skeleton* skeleton, float dt);

	virtual void attacking(Skeleton* skeleton) = 0;
    virtual void start_falling(Skeleton* skeleton) {}
	virtual ~SkeletonState();
};

class skeletonIdle : public SkeletonState
{
public:
	skeletonIdle(Skeleton* skeleton);
	
	void update(Skeleton* skeleton, float dt);
	void handle_events(Skeleton* skeleton, const sf::Event& event);
	void attacking(Skeleton* skeleton);
};

class skeletonRunning : public SkeletonState
{
private:
	static float running_speed;
public:
	skeletonRunning(Skeleton* skeleton);

	void update(Skeleton* skeleton, float dt);
	void handle_events(Skeleton* skeleton, const sf::Event& event);
	void attacking(Skeleton* skeleton);
};

