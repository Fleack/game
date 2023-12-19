#pragma once

#include "../Player.hpp"

#include <string>
#include <unordered_map>

class Player;

class EducationActivity
{
public:
    EducationActivity(std::string const& name, uint8_t energyDecrease, uint8_t happienesDecrease, uint32_t cost, std::unordered_map<skills_e, int16_t> skills);
    ~EducationActivity();

    bool perform(Player& player) const noexcept;
    std::string name() noexcept { return m_name; }

    std::string const& getName() const noexcept { return m_name; }
    uint8_t getEnergy() const noexcept { return m_energyDecrease; }
    uint8_t getHappiness() const noexcept { return m_happinessDecrease; }

private:
    inline static uint32_t g_next_id{0};
    std::string m_name;
    uint32_t m_id;
    uint8_t m_energyDecrease;
    uint8_t m_happinessDecrease;
    uint32_t m_cost;

    std::unordered_map<skills_e, int16_t> m_skills;
};
