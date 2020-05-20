#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "player.h"
#include "animation.h"
class Item
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	bool is_picked;
	Animation animation;
	int size_x;
	int size_y;
	float scale_factor;

public:
	Item(sf::Vector2f position);
	sf::Vector2f get_position() const;
	void update(Player& player, float dt);
	void draw(sf::RenderWindow& window);
	void set_position(sf::Vector2f position);

	friend class Player;
	friend class TileWorld;
};