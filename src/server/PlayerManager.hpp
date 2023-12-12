#pragma once

#include <string>

class EntertainmentActivity;
class IActivity;
class Player;

class PlayerManager
{
public:
    PlayerManager() = default;
    ~PlayerManager() noexcept;

    [[nodiscard]] bool createPlayer(std::string const& name) noexcept;

    Player* getPlayer() const noexcept;

    void passYear() const noexcept;
    void performEntertainmentActivity(EntertainmentActivity&) const noexcept;
    [[nodiscard]] bool performEducationCourse(std::string const& courseName) const noexcept;
    [[nodiscard]] bool performJob() const noexcept;

private:
    Player* m_player;
};
