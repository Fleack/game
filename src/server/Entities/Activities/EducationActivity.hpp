#pragma once

#include "IActivity.hpp"

class Player;

class EducationActivity : public IActivity
{
public:
    void perform(Player& player) const noexcept override;
};

class MathCourse final : public EducationActivity
{
public:
    void perform(Player& player) const noexcept override;
    std::string name() const noexcept override { return "Math course"; }
};

class HistoryCourse final : public EducationActivity
{
public:
    void perform(Player& player) const noexcept override;
    std::string name() const noexcept override { return "History course"; }
};

class PhysicsCourse final : public EducationActivity
{
public:
    void perform(Player& player) const noexcept override;
    std::string name() const noexcept override { return "Physics course"; }
};

class LiteratureCourse final : public EducationActivity
{
public:
    void perform(Player& player) const noexcept override;
    std::string name() const noexcept override { return "Literature course"; }
};

class ProgrammingCourse final : public EducationActivity
{
public:
    void perform(Player& player) const noexcept override;
    std::string name() const noexcept override { return "Programming course"; }
};
