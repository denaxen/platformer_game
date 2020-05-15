#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "animation.h"
#include "skeleton.h"
#include "skeleton_states.h"
#include "skeleton_strategy.h"

const int pursue_dist = 200; //from this distantion skeleton will pursue hero

using namespace std;

class Skeleton;
class Player;
class SkeletonState;

SkeletonStrategy::SkeletonStrategy() {};

void SkeletonStrategy::update(Skeleton* skeleton, Player& player, float dt) {
    skeleton->set_state(new skeletonIdle(skeleton));
    skeleton->state->update(skeleton, dt);
};

SkeletonStrategy::~SkeletonStrategy() {};



Wait::Wait(Skeleton* skeleton)
{
    skeleton->set_state(new skeletonIdle(skeleton));
    skeleton->velocity = {0, 0};
    
}

void Wait::update(Skeleton* skeleton, Player& player, float dt)
{
    skeleton->state->update(skeleton, dt);
    if (abs(player.get_position().x - skeleton->get_position().x) <= pursue_dist && abs(player.get_position().x - skeleton->get_position().x) > 1)
    {
        skeleton->set_strategy(new Pursue(skeleton));
    }
}

Pursue::Pursue(Skeleton* skeleton)
{
    skeleton->set_state(new skeletonRunning(skeleton));
}

void Pursue::update(Skeleton* skeleton, Player& player, float dt)
{
    skeleton->state->update(skeleton, dt);
    if (abs(player.get_position().x - skeleton->get_position().x) > pursue_dist)
    {
        skeleton->set_strategy(new Wait(skeleton));
        return;
    }
    if ((player.get_position() - skeleton->get_position()).x < -5)
    {
        skeleton->velocity = {-100, 0};
        skeleton->is_faced_right = false;
        return;
    }
    if ((player.get_position().x - skeleton->get_position().x) > 5)
    {
        skeleton->velocity = {100, 0};
        skeleton->is_faced_right = true;
        return;
    }
    if ((player.get_position() - skeleton->get_position()).x < 1 && (player.get_position() - skeleton->get_position()).x > -1)
    {
        skeleton->set_strategy(new Wait(skeleton));
    }

}