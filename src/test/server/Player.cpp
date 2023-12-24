#include "Player.hpp"

#include "Activities/JobActivity.hpp"

#include <gtest/gtest.h>

TEST(PlayerTest, IncreaseDecreaseHealth)
{
    Player player("ASD");
    player.increaseHealth(20);
    ASSERT_EQ(100, player.getHealth());

    player.decreaseHealth(10);
    ASSERT_EQ(90, player.getHealth());

    player.decreaseHealth(101);
    ASSERT_EQ(0, player.getHealth());
}

TEST(PlayerTest, IncreaseDecreaseEnergy)
{
    Player player("BASD");
    player.increaseEnergy(30);
    ASSERT_EQ(100, player.getEnergy());

    player.decreaseEnergy(15);
    ASSERT_EQ(85, player.getEnergy());

    player.decreaseEnergy(101);
    ASSERT_EQ(0, player.getEnergy());
}

TEST(PlayerTest, IncreaseDecreaseHappiness)
{
    Player player("GGGG");
    player.increaseHappiness(40);
    ASSERT_EQ(100, player.getHappiness());

    player.decreaseHappiness(25);
    ASSERT_EQ(75, player.getHappiness());

    player.decreaseHappiness(101);
    ASSERT_EQ(0, player.getHappiness());
}

TEST(PlayerTest, IncreaseDecreaseMoney)
{
    Player player("RAD");
    ASSERT_EQ(500, player.getMoney());

    player.increaseMoney(1000);
    ASSERT_EQ(1500, player.getMoney());

    player.decreaseMoney(500);
    ASSERT_EQ(1000, player.getMoney());

    player.decreaseMoney(10000);
    ASSERT_EQ(0, player.getMoney());
}

TEST(PlayerTest, IncreaseAge)
{
    Player player("NIL");
    player.increaseAge();
    ASSERT_EQ(19, player.getAge());
}

TEST(PlayerTest, IncreaseDecreaseSkill)
{
    Player player("QWE");
    player.increaseSkill(skills_e::MATH, 15);
    ASSERT_EQ(15, player.getSkills().at(skills_e::MATH));

    player.decreaseSkill(skills_e::MATH, 5);
    ASSERT_EQ(10, player.getSkills().at(skills_e::MATH));
}

TEST(PlayerTest, SetRemoveJob)
{
    Player player("HGF");
    auto job = std::make_unique<JobActivity>("Software Developer", 1000, 5000, 10, 5, 5);
    player.setJob(std::move(job));

    ASSERT_NE(nullptr, player.getJob());

    ASSERT_TRUE(player.removeJob());
    ASSERT_EQ(nullptr, player.getJob());
}

TEST(PlayerTest, PerformJob)
{
    Player player("NMB");
    auto job = std::make_unique<JobActivity>("Software Developer", 1000, 5000, 10, 5, 5);
    player.setJob(std::move(job));

    ASSERT_EQ(perform_job_error_e::OK, player.performJob());
}
