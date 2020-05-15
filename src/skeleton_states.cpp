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
    animation = Animation({0, 0, 24, 32}, 11, 12);
    cout << "Creating skeletonIdle state" << endl;
}

void skeletonIdle::attacking(Skeleton* skeleton)
{
}

void skeletonIdle::update(Skeleton* skeleton, float dt)
{
    animation.update(dt);
}

float skeletonRunning::running_speed = 400;

skeletonRunning::skeletonRunning(Skeleton* skeleton) : SkeletonState()
{
    animation = Animation({0, 40, 22, 33}, 11, 12);
    cout << "Creating skeletonRunning state" << endl;
}


void skeletonRunning::attacking(Skeleton* skeleton)
{
}

void skeletonRunning::update(Skeleton* skeleton, float dt)
{
    animation.update(dt);
}