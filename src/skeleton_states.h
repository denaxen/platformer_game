#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "skeleton.h"
#include "skeleton_strategy.h"

class Skeleton;

class SkeletonState
{
protected:
	Animation animation;
	static float running_speed;
public:
	SkeletonState();

	sf::Vector2i get_size();
	void set_sprite(sf::Sprite& sprite, bool is_faced_right);

	virtual void update(Skeleton* skeleton, float dt);

	virtual ~SkeletonState();
	friend class Pursue;
	friend class Wait;
	friend class Attacking;
};

class skeletonIdle : public SkeletonState
{
public:
	skeletonIdle(Skeleton* skeleton);
	
	void update(Skeleton* skeleton, float dt);
};

class skeletonRunning : public SkeletonState
{
public:
	skeletonRunning(Skeleton* skeleton);

	void update(Skeleton* skeleton, float dt);
};

class skeletonAttack : public SkeletonState
{
public:
	skeletonAttack(Skeleton* skeleton);

	void update(Skeleton* skeleton, float dt);
};