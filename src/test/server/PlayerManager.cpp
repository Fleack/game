#include "PlayerManager.hpp"

#include "Activities/EducationActivity.hpp"
#include "Activities/EntertainmentActivity.hpp"

#include <gtest/gtest.h>

TEST(PlayerManagerTest, CreatePlayer)
{
    PlayerManager playerManager;
    ASSERT_TRUE(playerManager.createPlayer("BOBA"));

    Player* player = playerManager.getPlayer();
    ASSERT_NE(nullptr, player);
    ASSERT_EQ("BOBA", player->getName());
}

TEST(PlayerManagerTest, PassYear)
{
    PlayerManager playerManager;
    ASSERT_TRUE(playerManager.createPlayer("BIBA"));

    Player* player = playerManager.getPlayer();
    ASSERT_NE(nullptr, player);

    int initialAge = player->getAge();
    playerManager.passYear();

    ASSERT_EQ(initialAge + 1, player->getAge());
    ASSERT_EQ(100, player->getEnergy());
}

TEST(PlayerManagerTest, PerformEntertainmentActivity)
{
    PlayerManager playerManager;
    ASSERT_TRUE(playerManager.createPlayer("BOBUS"));

    Player* player = playerManager.getPlayer();
    ASSERT_NE(nullptr, player);

    EntertainmentActivity activity;
    ASSERT_TRUE(playerManager.performEntertainmentActivity(activity));
}

TEST(PlayerManagerTest, PerformEducationCourse)
{
    PlayerManager playerManager;
    ASSERT_TRUE(playerManager.createPlayer("BEBE"));

    Player* player = playerManager.getPlayer();
    ASSERT_NE(nullptr, player);

    ASSERT_FALSE(playerManager.performEducationCourse("Programming 101")); // No money
}

TEST(PlayerManagerTest, PerformJob)
{
    PlayerManager playerManager;
    ASSERT_TRUE(playerManager.createPlayer("BEBRUS"));

    Player* player = playerManager.getPlayer();
    ASSERT_NE(nullptr, player);

    perform_job_error_e result = playerManager.performJob();
    ASSERT_EQ(perform_job_error_e::UNSPECIFIED, result); // No job
}
