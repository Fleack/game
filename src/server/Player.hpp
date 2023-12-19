#pragma once

#include "Activities/JobActivity.hpp"

#include <memory>
#include <string>
#include <unordered_map>

enum class skills_e
{
    MATH,
    HISTORY,
    PHYSICS,
    LITERATURE,
    PROGRAMMING,
};

enum class perform_job_error_e
{
    OK,
    ENERGY,
    HEALTH,
    HAPPINESS,
    UNSPECIFIED,
};

class Player
{
public:
    explicit Player(std::string const&) noexcept;

    void increaseHealth(uint8_t) noexcept;
    void decreaseHealth(uint8_t) noexcept;

    void increaseEnergy(uint8_t) noexcept;
    void decreaseEnergy(uint8_t) noexcept;

    void increaseHappiness(uint8_t) noexcept;
    void decreaseHappiness(uint8_t) noexcept;

    void increaseMoney(uint32_t) noexcept;
    void decreaseMoney(uint32_t) noexcept;

    void increaseAge() noexcept;

    void increaseSkill(skills_e, uint8_t);
    void decreaseSkill(skills_e, uint8_t);

    void setJob(std::unique_ptr<JobActivity>&&) noexcept;
    bool removeJob() noexcept;

    std::unordered_map<skills_e, uint8_t> const& getSkills() const noexcept;
    std::string const& getName() const noexcept;
    uint8_t getHealth() const noexcept;
    uint8_t getEnergy() const noexcept;
    uint8_t getHappiness() const noexcept;
    uint8_t getAge() const noexcept;
    uint32_t getMoney() const noexcept;
    JobActivity const* getJob() const noexcept;

    perform_job_error_e performJob() noexcept;

private:
    std::string m_name;
    uint8_t m_health{100};
    uint8_t m_energy{100};
    uint8_t m_happiness{100};
    uint32_t m_money{500}; // TODO Rework with negative amount of money(aka debt)
    uint8_t m_age{18};

    std::unique_ptr<JobActivity> m_job{nullptr};

    std::unordered_map<skills_e, uint8_t> m_skills;
};