#pragma once

#include <string>

class Player;

class EducationActivity
{
public:
    EducationActivity(std::string&& name, uint8_t energyDecrease, uint8_t happienesDecrease);
    ~EducationActivity();

    void perform(Player& player) noexcept;
    std::string name() noexcept { return m_name; }

    std::string const& getName() const noexcept { return m_name; }
    uint8_t getEnergy() const noexcept { return m_energyDecrease; }
    uint8_t getHappiness() const noexcept { return m_happinessDecrease; }

private:
    static uint32_t g_next_id;
    std::string m_name;
    uint32_t m_id;
    uint8_t m_energyDecrease;
    uint8_t m_happinessDecrease;
};
