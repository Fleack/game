#pragma once

#include "IActivity.hpp"

class Player;

class EntertainmentActivity final : public IActivity
{
public:
    void perform(Player& player) const noexcept override;
    std::string name() const noexcept override { return "Entertainment activity"; }
};
