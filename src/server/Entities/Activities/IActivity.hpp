#pragma once

#include <string>

class Player;

class IActivity
{
public:
    virtual ~IActivity() = default;
    virtual void perform(Player& player) const noexcept = 0;
    virtual std::string name() const noexcept = 0;
};
