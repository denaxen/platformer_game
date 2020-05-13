#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "animation.h"
#include "skeleton.h"
#include "skeleton_states.h"

using namespace std;

SkeletonState::SkeletonState() {};

void SkeletonState::update(Skeleton* skeleton, float dt)
{
    animation.update(dt);
}

sf::Vector2i SkeletonState::get_size()
{
    return animation.get_size();
}
void SkeletonState::set_sprite(sf::Sprite& sprite, bool is_faced_right)
{
    animation.set_sprite(sprite, is_faced_right);
}
SkeletonState::~SkeletonState() {};




skeletonIdle::skeletonIdle(Skeleton* skeleton) : SkeletonState()
{
    skeleton->velocity = {0, 0};
    animation = Animation({4, 0, 19, 34}, 12, 12);
    cout << "Creating skeletonIdle state" << endl;
}

void skeletonIdle::attacking(Skeleton* skeleton)
{
}

void skeletonIdle::update(Skeleton* skeleton, float dt)
{
    animation.update(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        skeleton->set_state(new skeletonRunning(skeleton));
        return;
    }
}

float skeletonRunning::running_speed = 400;

skeletonRunning::skeletonRunning(Skeleton* skeleton) : SkeletonState()
{
    animation = Animation({0, 64, 21, 34}, 8, 12);
    cout << "Creating skeletonRunning state" << endl;
}


void skeletonRunning::attacking(Skeleton* skeleton)
{
}

void skeletonRunning::update(Skeleton* skeleton, float dt)
{
    animation.update(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        skeleton->velocity.x = -running_speed;
        skeleton->is_faced_right = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        skeleton->velocity.x = running_speed;
        skeleton->is_faced_right = true;
    }
}