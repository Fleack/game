#include "PlayerManager.hpp"

#include "Activities/EducationActivity.hpp"
#include "Player.hpp"

#include <iostream>

#include <Activities/EntertainmentActivity.hpp>

PlayerManager::~PlayerManager() noexcept
{
    delete m_player;
}

bool PlayerManager::createPlayer(std::string const& name) noexcept
{
    try
    {
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
    m_player->increaseAge();
    m_player->increaseEnergy(100);
    std::cout << "Year passed" << std::endl;
}

void PlayerManager::performEntertainmentActivity(EntertainmentActivity& activity) const noexcept
{
    activity.perform(*m_player);
    std::cout << "Permormed activity: " << activity.name() << std::endl;
}

bool PlayerManager::performEducationCourse(std::string const&) const noexcept
{
    // TODO rework with new EducationActivity impl
    return true;
}

bool PlayerManager::performJob() const noexcept
{
    if (!m_player)
    {
        return false;
    }
    m_player->performJob();
    return true;
}
