#pragma once

#include <cstdint>
#include <string>

enum class perform_job_error_e;
class Player;

class JobActivity
{
public:
    JobActivity(std::string&& name, uint32_t salaryMin, uint32_t salaryMax, uint8_t energyDecrease, uint8_t healthDecrease, uint8_t happienesDecrease);
    ~JobActivity();

    perform_job_error_e perform(Player& player) noexcept;
    std::string name() noexcept { return m_name; }

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
