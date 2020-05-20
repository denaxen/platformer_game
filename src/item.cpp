#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "item.h"
#include "player.h"



Item::Item(sf::Vector2f position)
{
	if (!texture.loadFromFile("../textures/portal.png"))
	{
		std::cout << "Can't load image ./portal.png for Item class" << std::endl;
		exit(1);
	}
	size_x = 16;
	size_y = 13;
	sprite.setTexture(texture);
	sprite.setPosition(position);
	animation = Animation({0, 2, size_x, size_y}, 1, 1);
	scale_factor = 7;
	sprite.setScale(scale_factor, scale_factor);
	is_picked = false;
	
}

sf::Vector2f Item::get_position() const
{
	return sprite.getPosition();
}

void Item::update(Player& player, float dt)
{
	if(abs(player.sprite.getPosition().x - sprite.getPosition().x) < 40 && abs(player.sprite.getPosition().y - sprite.getPosition().y) < 60)
	{
		is_picked = true;
	}
}

void Item::draw(sf::RenderWindow& window)
{
	if(!is_picked)
	{
	    window.draw(sprite);
	}
}


void Item::set_position(sf::Vector2f position)
{
	sprite.setPosition(position);
}

