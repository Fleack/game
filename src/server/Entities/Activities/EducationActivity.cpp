#include "EducationActivity.hpp"

#include "../Player.hpp" // Fix this somehow

void EducationActivity::perform(Player& player) const noexcept
{
    player.decreaseEnergy(15);
    player.decreaseMoney(30);
    player.increaseHappiness(10);
}

void MathCourse::perform(Player& player) const noexcept
{
    EducationActivity::perform(player);
    player.increaseSkill(skills_e::MATH, 10);
}

void HistoryCourse::perform(Player& player) const noexcept
{
    EducationActivity::perform(player);
    player.increaseSkill(skills_e::HISTORY, 10);
}

void PhysicsCourse::perform(Player& player) const noexcept
{
    EducationActivity::perform(player);
    player.increaseSkill(skills_e::PHYSICS, 10);
}

void LiteratureCourse::perform(Player& player) const noexcept
{
    EducationActivity::perform(player);
    player.increaseSkill(skills_e::LITERATURE, 10);
}

void ProgrammingCourse::perform(Player& player) const noexcept
{
    EducationActivity::perform(player);
    player.increaseSkill(skills_e::PROGRAMMING, 10);
}
