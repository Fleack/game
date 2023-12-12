#pragma once

#include <string>

class IActivity;
class Player;

class PlayerManager
{
public:
    PlayerManager();
    ~PlayerManager() noexcept;

    [[nodiscard]] bool createPlayer(std::string const& name) noexcept;

    Player* getPlayer() const noexcept;

    void passYear() const noexcept;
    void performActivity(IActivity const&) const noexcept;
    [[nodiscard]] bool performEducationCourse(std::string const& courseName) const noexcept;
    void performJob() const noexcept;

private:
    Player* m_player;
};
