#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "skeleton.h"
#include "skeleton_states.h"
#include "skeleton_strategy.h"
#include "tiles.h"




void Skeleton::set_state(SkeletonState* new_state)
{
    delete state;
    state = new_state;
}

void Skeleton::set_strategy(SkeletonStrategy* new_strategy)
{
    delete strategy;
    strategy = new_strategy;
}

Skeleton::Skeleton(sf::Vector2f position)
{
    if (!texture.loadFromFile("../textures/skeleton.png"))
    {
        std::cout << "Can't load image ./skeleton.png for Skeleton class" << std::endl;
        exit(1);
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    //sprite.setOrigin(.getSize().x, texture.getSize().y);

    scale_factor = 3;
    sprite.setScale(scale_factor, scale_factor);
    state = new skeletonIdle(this);
    strategy = new Pursue(this);
    
}

sf::Vector2f Skeleton::get_center() const
{
    return {sprite.getPosition().x + state->get_size().x * scale_factor / 2,
            sprite.getPosition().y + state->get_size().y * scale_factor / 2};
}

sf::Vector2f Skeleton::get_position() const
{
    return sprite.getPosition();
}
void Skeleton::set_position(sf::Vector2f position)
{
    sprite.setPosition(position);
}


void Skeleton::update(Player& player, float dt)
{
    strategy->update(this, player, dt);
    sprite.move(velocity * dt);
}

void Skeleton::draw(sf::RenderWindow& window)
{
    sf::FloatRect skeleton_rect = {sprite.getPosition().x, sprite.getPosition().y,
                                 state->get_size().x * scale_factor, state->get_size().y * scale_factor};

    sf::RectangleShape test({skeleton_rect.width, skeleton_rect.height});
    test.setPosition({skeleton_rect.left, skeleton_rect.top});
    test.setFillColor(sf::Color(0, 255, 0, 150));
    state->set_sprite(sprite, is_faced_right);
    window.draw(sprite);
}

bool Skeleton::handle_collision(const sf::FloatRect& rect, bool is_hookable)
{
    sf::FloatRect player_rect = {sprite.getPosition().x, sprite.getPosition().y,
                                 state->get_size().x * scale_factor, state->get_size().y * scale_factor};
    float overlapx1 = player_rect.left + player_rect.width - rect.left;
    float overlapx2 = rect.left + rect.width - player_rect.left;
    float overlapy1 = player_rect.top + player_rect.height - rect.top;
    float overlapy2 = rect.top + rect.height - player_rect.top;

    if (overlapx1 > 0 && overlapx2 > 0 && overlapy1 > 0 && overlapy2 > 0)
    {
        int min_overlap_direction = 0;
        float min_ovelap = overlapx1;
        if (overlapx2 < min_ovelap) {min_overlap_direction = 1; min_ovelap = overlapx2;}
        if (overlapy1 < min_ovelap) {min_overlap_direction = 2; min_ovelap = overlapy1;}
        if (overlapy2 < min_ovelap) {min_overlap_direction = 3; min_ovelap = overlapy2;}

        switch (min_overlap_direction)
        {
            case 0:
                sprite.move({-overlapx1, 0});
                velocity.x = 0;
                break;
            case 1:
                sprite.move({overlapx2, 0});
                velocity.x = 0;
                break;
            case 2:
                sprite.move({0, -overlapy1});
                velocity.y = 0;
                break;
            case 3:
                sprite.move({0, overlapy2});
                if (velocity.y < 0)
                    velocity.y = 0;
                break;
        }
        return true;
    }
    else
    {
        return false;
    }
}

void Skeleton::handle_all_collisions(sf::Vector2i tile_counts, sf::Vector2f tile_sizes, const std::vector<Tile>& tilemap)
{
    bool is_colided = false;
    sf::Vector2i player_tile_coordinates_topleft;
    player_tile_coordinates_topleft.x = (int)sprite.getPosition().x / tile_sizes.x;
    player_tile_coordinates_topleft.y = (int)sprite.getPosition().y / tile_sizes.y;

    sf::Vector2i player_tile_coordinates_bottomright;
    player_tile_coordinates_bottomright.x = (int)(sprite.getPosition().x + state->get_size().x * scale_factor) / tile_sizes.x;
    player_tile_coordinates_bottomright.y = (int)(sprite.getPosition().y + state->get_size().y * scale_factor) / tile_sizes.y;

    for (int i = player_tile_coordinates_topleft.x; i <= player_tile_coordinates_bottomright.x; i++)
    {
        for (int j = player_tile_coordinates_topleft.y; j <= player_tile_coordinates_bottomright.y; j++)
        {
            if (tilemap[i + tile_counts.x * j] != Tile::None)
            {
                bool is_hookable = false;
                if (j != 0 && tilemap[i + tile_counts.x * (j - 1)] == Tile::None)
                    is_hookable = true;
                handle_collision({tile_sizes.x * i, tile_sizes.y * j, tile_sizes.x, tile_sizes.y}, is_hookable);
                is_colided = true;
            }
        }

    }
}


Skeleton::~Skeleton()
{
    delete state;
}