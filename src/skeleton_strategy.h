#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "skeleton.h"
#include "skeleton_states.h"
#include "player.h"

class Skeleton;
class Player;
class SkeletonState;

class SkeletonStrategy
{
private:
    SkeletonState* state;
    float time;
public:
    SkeletonStrategy();

    virtual void update(Skeleton* skeleton, Player& player, float dt);

    virtual ~SkeletonStrategy();
};

class Wait : public SkeletonStrategy
{
public:
    Wait(Skeleton* skeleton);

    void update(Skeleton* skeleton, Player& player, float dt);
};

class Pursue : public SkeletonStrategy
{
public:
    Pursue(Skeleton* skeleton);

    void update(Skeleton* skeleton, Player& player, float dt);
};

class Attacking : public SkeletonStrategy
{
public:
    Attacking(Skeleton* skeleton);

    void update(Skeleton* skeleton, Player& player, float dt);
};