#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "skeleton_states.h"
#include "skeleton_strategy.h"
#include "tiles.h"

class SkeletonState;
class SkeletonStrategy;

class Skeleton
{
private:
    SkeletonState* state;
	SkeletonStrategy* strategy;
	
	sf::Texture texture;
	sf::Sprite sprite;

	bool is_faced_right;
	sf::Vector2f velocity;
	float scale_factor;

	//const float jumping_velocity = 1260;
	void set_state(SkeletonState* new_state);
	void set_strategy(SkeletonStrategy* new_strategy);

public:
	Skeleton(sf::Vector2f position);

	sf::Vector2f get_center() const;
	sf::Vector2f get_position() const;
	void set_position(sf::Vector2f position);

	void update(Player& player, float dt);
	void draw(sf::RenderWindow& window);
	bool handle_collision(const sf::FloatRect& rect, bool is_hookable);
	void handle_all_collisions(sf::Vector2i tile_counts, sf::Vector2f tile_sizes, const std::vector<Tile>& tilemap);


	~Skeleton();

	friend class SkeletonState;
	friend class skeletonIdle;
	friend class skeletonRunning;
	friend class skeletonAttack;
	friend class SkeletonStrategy;
	friend class Wait;
	friend class Pursue;
	friend class Attacking;
};