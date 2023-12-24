#include "PlayerManager.hpp"

#include "Activities/EducationActivity.hpp"
#include "Activities/EntertainmentActivity.hpp"
#include "Player.hpp"

#include <iostream>

PlayerManager::~PlayerManager() noexcept
{
    delete m_player;
}

bool PlayerManager::createPlayer(std::string const& name) noexcept
{
    try
    {
        delete m_player;
        m_player = new Player{name};
        std::cout << "Created player: " << name << std::endl;
        return true;
    }
    catch (std::exception& e)
    {
        std::cout << "Couldn't create player:" << e.what() << std::endl;
        return false;
    }
}

Player* PlayerManager::getPlayer() const noexcept
{
    return m_player;
}

void PlayerManager::passYear() const noexcept
{
    if (!m_player) { return; }
    m_player->increaseAge();
    m_player->increaseEnergy(100);
    std::cout << "Year passed" << std::endl;
}

bool PlayerManager::performEntertainmentActivity(EntertainmentActivity& activity) const noexcept
{
    if (!m_player) { return false; }
    std::cout << "Permormed activity: " << activity.name() << std::endl;
    return activity.perform(*m_player);
}

bool PlayerManager::performEducationCourse(std::string const&) const noexcept
{
    if (!m_player) { return false; }
    // TODO rework
    std::unordered_map<skills_e, int16_t> const skills{
        {skills_e::MATH, 10},
        {skills_e::HISTORY, 10},
        {skills_e::PHYSICS, 10},
        {skills_e::LITERATURE, 10},
        {skills_e::PROGRAMMING, 10}};
    EducationActivity const activity("course", 10, 10, 10'000, skills);
    return activity.perform(*m_player);
    ;
}

perform_job_error_e PlayerManager::performJob() const noexcept
{
    if (!m_player) { return perform_job_error_e::UNSPECIFIED; }
    return m_player->performJob();
}
