#pragma once

#include <string>

class Player;

class EntertainmentActivity
{
public:
    EntertainmentActivity();
    ~EntertainmentActivity();
    bool perform(Player& player) noexcept;
    std::string name() noexcept { return "Entertainment activity"; }
};
