#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "animation.h"
#include "skeleton.h"
#include "skeleton_states.h"
#include "skeleton_strategy.h"

const int max_pursue_dist = 1000; //until this distantion skeleton pursue hero
const int min_pursue_dist = 60;   //from this distantion skeleton pursue hero
const int stop_pursue_dist = 30; //from this distantion skeleton STOP pursue hero

using namespace std;

class Skeleton;
class Player;
class SkeletonState;
class Animation;

SkeletonStrategy::SkeletonStrategy() {};

void SkeletonStrategy::update(Skeleton* skeleton, Player& player, float dt) {
    skeleton->set_state(new skeletonIdle(skeleton));
    skeleton->state->update(skeleton, dt);
}

SkeletonStrategy::~SkeletonStrategy() {};



Wait::Wait(Skeleton* skeleton)
{
    skeleton->velocity = {skeleton->state->running_speed, 0};
    skeleton->is_faced_right = true;
    skeleton->set_state(new skeletonRunning(skeleton));
}

void Wait::update(Skeleton* skeleton, Player& player, float dt)
{
    if (skeleton->velocity.x == 0 && skeleton->is_faced_right)
    {
        skeleton->velocity.x = -skeleton->state->running_speed;
        skeleton->is_faced_right = !skeleton->is_faced_right;
    }
    if (skeleton->velocity.x == 0 && !skeleton->is_faced_right)
    {
        skeleton->velocity.x = skeleton->state->running_speed;
        skeleton->is_faced_right = !skeleton->is_faced_right;
    }
    skeleton->state->update(skeleton, dt);
    if (abs(player.get_position().x - skeleton->get_position().x) <= max_pursue_dist && 
        abs(player.get_position().x - skeleton->get_position().x) >= min_pursue_dist && abs(player.get_position().y - skeleton->get_position().y) <= 30)
    {
        skeleton->set_strategy(new Pursue(skeleton));
    }
    if (abs(player.get_position().x - skeleton->get_position().x) <= min_pursue_dist && abs(player.get_position().y - skeleton->get_position().y) <= 30)
    {
        skeleton->set_strategy(new Attacking(skeleton));
    }
}

Pursue::Pursue(Skeleton* skeleton)
{
    skeleton->set_state(new skeletonRunning(skeleton));
}

void Pursue::update(Skeleton* skeleton, Player& player, float dt)
{
    skeleton->state->update(skeleton, dt);
    if (abs(player.get_position().x - skeleton->get_position().x) >= max_pursue_dist || 
    abs(player.get_position().y - skeleton->get_position().y) >= 100) //stop purs
    {
        skeleton->set_strategy(new Wait(skeleton));
        
        return;
    }
    if (abs(player.get_position().x - skeleton->get_position().x) < stop_pursue_dist)
    {
        skeleton->velocity.x = 0;
        skeleton->set_strategy(new Attacking(skeleton));
        return;
    }
    if ((player.get_position() - skeleton->get_position()).x < -1) //direction of running
    {
        skeleton->velocity = {-skeleton->state->running_speed, 0};
        skeleton->is_faced_right = false;
        return;
    }
    if ((player.get_position().x - skeleton->get_position().x) > 1) //direction of running
    {
        skeleton->velocity = {skeleton->state->running_speed, 0};
        skeleton->is_faced_right = true;
        return;
    }
    
}

Attacking::Attacking(Skeleton* skeleton)
{
    skeleton->set_state(new skeletonAttack(skeleton));
}


void Attacking::update(Skeleton* skeleton, Player& player, float dt)
{
    if (skeleton->state->animation.current_frame == 15)
    {
        player.is_lose = true;
    }
    skeleton->state->update(skeleton, dt);
    if (abs(player.get_position().x - skeleton->get_position().x) >= min_pursue_dist || 
    abs(player.get_position().y - skeleton->get_position().y) >= 200)
        skeleton->set_strategy(new Pursue(skeleton));
}