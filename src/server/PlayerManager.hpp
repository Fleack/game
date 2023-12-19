#pragma once

#include "Player.hpp"

#include <string>

class EntertainmentActivity;
class IActivity;

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
    [[nodiscard]] perform_job_error_e performJob() const noexcept;

private:
    Player* m_player{nullptr};
};
