#include "JobActivity.hpp"

#include "../Player.hpp"

#include <random>

uint32_t JobActivity::g_next_id = 0;

JobActivity::JobActivity(std::string&& name, uint32_t const salaryMin, uint32_t const salaryMax, uint8_t const energyDecrease, uint8_t const healthDecrease, uint8_t const happienesDecrease)
    : m_name(std::move(name))
    , m_id(g_next_id++)
    , m_energyDecrease(energyDecrease)
    , m_healthDecrease(healthDecrease)
    , m_happienesDecrease(happienesDecrease)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(salaryMin, salaryMax);
    m_salary = dist(gen);
}

JobActivity::~JobActivity() = default;

perform_job_error_e JobActivity::perform(Player& player) noexcept
{
    using enum perform_job_error_e;
    if (m_energyDecrease > player.getEnergy()) { return ENERGY; }
    if (m_happienesDecrease > player.getHappiness()) { return HAPPINESS; }
    if (m_healthDecrease > player.getHealth()) { return HEALTH; }

    player.decreaseEnergy(m_energyDecrease);
    player.decreaseHappiness(m_happienesDecrease);
    player.decreaseHealth(m_healthDecrease);
    player.increaseMoney(m_salary);
    return OK;
}
