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
    if (player.getMoney() < 500)
    {
        return false;
    }
    player.increaseHappiness(15);
    player.increaseEnergy(5);
    player.increaseHealth(5);
    player.decreaseMoney(500);
    return true;
}
