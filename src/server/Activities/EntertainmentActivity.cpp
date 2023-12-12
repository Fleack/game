#include "EntertainmentActivity.hpp"

#include "../Player.hpp"

void EntertainmentActivity::perform(Player& player) const noexcept
{
    player.increaseHappiness(20);
    player.decreaseEnergy(10);
    player.increaseHealth(5);
    player.decreaseMoney(500);
}
