#include "EntertainmentActivity.hpp"

#include "../Player.hpp"

#include <iostream>

EntertainmentActivity::EntertainmentActivity()
{
    std::cout << "nigga";
}

EntertainmentActivity::~EntertainmentActivity()
{
}

void EntertainmentActivity::perform(Player& player) noexcept
{
    player.increaseHappiness(20);
    player.decreaseEnergy(10);
    player.increaseHealth(5);
    player.decreaseMoney(500);
}
