#include "PlayerManager.hpp"

#include "Activities/EducationActivity.hpp"
#include "Activities/IActivity.hpp"
#include "Logger.hpp"
#include "Player.hpp"

PlayerManager::~PlayerManager() noexcept
{
    delete m_player;
}

void PlayerManager::passYear() const noexcept
{
    m_player->increaseAge();
    m_player->increaseEnergy(100);
    LOG(info) << "Year passed" << std::endl;
}

void PlayerManager::performActivity(IActivity const& activity) const noexcept
{
    activity.perform(*m_player);
    LOG(info) << "Permormed activity: " << activity.name() << std::endl;
}

bool PlayerManager::createPlayer(std::string const& name) noexcept
{
    try
    {
        m_player = new Player{name};
        LOG(info) << "Created player: " << name << std::endl;
        return true;
    }
    catch (std::exception& e)
    {
        LOG(error) << "Couldn't create player:" << e.what() << std::endl;
        return false;
    }
}

bool PlayerManager::performEducationCourse(std::string const& courseName) const noexcept
{
    if (courseName == "math_course")
    {
        performActivity(MathCourse{});
    }
    else if (courseName == "history_course")
    {
        performActivity(HistoryCourse{});
    }
    else if (courseName == "physics_course")
    {
        performActivity(PhysicsCourse{});
    }
    else if (courseName == "literature_course")
    {
        performActivity(LiteratureCourse{});
    }
    else if (courseName == "programming_course")
    {
        performActivity(ProgrammingCourse{});
    }
    else
    {
        LOG(error) << "Incorrect course name" << std::endl;
        // TODO send error response
        return false;
    }
    return true;
}

void PlayerManager::performJob() const noexcept
{
    // Assume that m_player is not null,
    // because client doesn't allow sending the request before creating player
    m_player->performJob();
}
