#include "JobActivity.hpp"

#include "../Player.hpp"

#include <ctime>

JobActivity::JobActivity(std::string&& name, uint32_t const salaryMin, uint32_t const salaryMax, uint8_t const energyDecrease, uint8_t const healthDecrease, uint8_t const happienesDecrease)
    : m_name(std::move(name))
    , m_id(g_next_id++)
    , m_energyDecrease(energyDecrease)
    , m_healthDecrease(healthDecrease)
    , m_happienesDecrease(happienesDecrease)
{
    std::srand(static_cast<uint32_t>(std::time(nullptr)));
    m_salary = salaryMin + std::rand() % (salaryMax - salaryMin + 1);
}

void JobActivity::perform(Player& player) const noexcept
{
    player.decreaseEnergy(m_energyDecrease);
    player.decreaseHappiness(m_happienesDecrease);
    player.decreaseHealth(m_healthDecrease);
    player.increaseMoney(m_salary);
}


