#include "EducationActivity.hpp"

#include "../Player.hpp"

EducationActivity::EducationActivity(std::string const& name, uint8_t energyDecrease, uint8_t happienesDecrease, uint32_t cost, std::unordered_map<skills_e, int16_t> skills)
    : m_name{name}
    , m_energyDecrease{energyDecrease}
    , m_happinessDecrease{happienesDecrease}
    , m_cost{cost}
    , m_skills{skills}
    , m_id{g_next_id++}
{}

EducationActivity::~EducationActivity() = default;

bool EducationActivity::perform(Player& player) const noexcept
{
    if (player.getMoney() < m_cost ||
        player.getEnergy() < m_energyDecrease ||
        player.getHappiness() < m_happinessDecrease)
    {
        return false;
    }

    player.decreaseEnergy(m_energyDecrease);
    player.decreaseMoney(m_cost);
    player.increaseHappiness(m_happinessDecrease);
    for (auto const [skill, value] : m_skills)
    {
        player.increaseSkill(skill, value);
    }
    return true;
}
