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
    animation = Animation({1, 1, 24, 42}, 11, 12);
    cout << "Creating skeletonIdle state" << endl;
}


void skeletonIdle::update(Skeleton* skeleton, float dt)
{
    animation.update(dt);
}

float SkeletonState::running_speed = 200;

skeletonRunning::skeletonRunning(Skeleton* skeleton) : SkeletonState()
{
    animation = Animation({0, 43, 22, 42}, 11, 12);
    cout << "Creating skeletonRunning state" << endl;
}


void skeletonRunning::update(Skeleton* skeleton, float dt)
{
    animation.update(dt);
}

skeletonAttack::skeletonAttack(Skeleton* skeleton) : SkeletonState()
{
    animation = Animation({0, 167, 43, 42}, 18, 17);
    cout << "Creating skeletonAttack state" << endl;
}


void skeletonAttack::update(Skeleton* skeleton, float dt)
{
    animation.update(dt);
}