#include "EntertainmentActivity.hpp"

#include "../Player.hpp"

EntertainmentActivity::EntertainmentActivity()
{
}

EntertainmentActivity::~EntertainmentActivity()
{
}

bool EntertainmentActivity::perform(Player& player) noexcept
{
    if (player.getMoney() < 500) { return false; }
    if (player.getEnergy() < 5) { return false; }

    player.increaseHappiness(15);
    player.decreaseEnergy(5);
    player.increaseHealth(5);
    player.decreaseMoney(500);
    return true;
}
