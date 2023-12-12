#pragma once

#include "IActivity.hpp"

class JobActivity final
{
public:
    JobActivity(std::string&& name, uint32_t salaryMin, uint32_t salaryMax, uint8_t energyDecrease, uint8_t healthDecrease, uint8_t happienesDecrease);
    ~JobActivity() = default;

    void perform(Player& player) const noexcept;

    std::string const& getName() const noexcept { return m_name; }
    uint32_t getID() const noexcept { return m_id; }
    uint32_t getSalary() const noexcept { return m_salary; }
    uint8_t getEnergy() const noexcept { return m_energyDecrease; }
    uint8_t getHealth() const noexcept { return m_healthDecrease; }
    uint8_t getHappienes() const noexcept { return m_happienesDecrease; }

private:
    static uint32_t g_next_id;
    std::string m_name;
    uint32_t m_id;
    uint32_t m_salary;
    uint8_t m_energyDecrease;
    uint8_t m_healthDecrease;
    uint8_t m_happienesDecrease;
};
