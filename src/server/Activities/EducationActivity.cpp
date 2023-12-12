#include "EducationActivity.hpp"

#include "../Player.hpp"

EducationActivity::EducationActivity(std::string&& name, uint8_t energyDecrease, uint8_t happienesDecrease)
    : m_name{name}
    , m_energyDecrease{energyDecrease}
    , m_happinessDecrease{happienesDecrease}
    , m_id{g_next_id++}
{}

EducationActivity::~EducationActivity() = default;

void EducationActivity::perform(Player& player) noexcept
{
    player.decreaseEnergy(15);
    player.decreaseMoney(30);
    player.increaseHappiness(10);
}
