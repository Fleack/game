#include "Player.hpp"

#include <iostream>

#include <iostream>

Player::Player(std::string const& name) noexcept
    : m_name{name}
{}

void Player::increaseHealth(uint8_t const amount) noexcept
{
    m_health += amount;
    if (m_health > 100)
    {
        m_health = 100;
    }
}

void Player::decreaseHealth(uint8_t const amount) noexcept
{
    if (m_health < amount)
    {
        m_health = 0;
    }
    else
    {
        m_health -= amount;
    }
}

void Player::increaseEnergy(uint8_t const amount) noexcept
{
    m_energy += amount;
    if (m_energy > 100)
    {
        m_energy = 100;
    }
}

void Player::decreaseEnergy(uint8_t const amount) noexcept
{
    if (m_energy < amount)
    {
        m_energy = 0;
    }
    else
    {
        m_energy -= amount;
    }
}

void Player::increaseHappiness(uint8_t const amount) noexcept
{
    m_happiness += amount;
    if (m_happiness > 100)
    {
        m_happiness = 100;
    }
}

void Player::decreaseHappiness(uint8_t const amount) noexcept
{
    if (m_happiness < amount)
    {
        m_happiness = 0;
    }
    else
    {
        m_happiness -= amount;
    }
}

void Player::increaseMoney(uint32_t const amount) noexcept
{
    m_money += amount;
}
void Player::decreaseMoney(uint32_t const amount) noexcept
{
    if (m_money < amount)
    {
        m_money = 0;
    }
    else
    {
        m_money -= amount;
    }
}

void Player::increaseAge() noexcept
{
    m_age++;
}

void Player::increaseSkill(skills_e const skill, uint8_t const amount)
{
    m_skills[skill] += amount;
}

void Player::decreaseSkill(skills_e const skill, uint8_t const amount)
{

    if (m_skills[skill] < amount)
    {
        m_skills[skill] = 0;
    }
    else
    {
        m_skills[skill] -= amount;
    }
}

void Player::setJob(std::unique_ptr<JobActivity>&& job) noexcept
{
    if (!job)
    {
        std::cout << "Tried to set nullptr job";
        return;
    }
    m_job = std::move(job);
}

void Player::removeJob() noexcept
{
    if (!m_job)
    {
        std::cout << "Player already has no job";
    }
    m_job = nullptr;
}

std::unordered_map<skills_e, uint8_t> const& Player::getSkills() const noexcept
{
    return m_skills;
}

std::string const& Player::getName() const noexcept
{
    return m_name;
}

uint8_t Player::getHealth() const noexcept
{
    return m_health;
}

uint8_t Player::getEnergy() const noexcept
{
    return m_energy;
}

uint8_t Player::getHappiness() const noexcept
{
    return m_happiness;
}

uint8_t Player::getAge() const noexcept
{
    return m_age;
}

uint32_t Player::getMoney() const noexcept
{
    return m_money;
}

JobActivity const* Player::getJob() const noexcept
{
    return m_job.get();
}

void Player::performJob() noexcept
{
    if (m_job)
    {
        m_job->perform(*this);
    }
}
