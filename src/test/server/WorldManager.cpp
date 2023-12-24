#include "WorldManager.hpp"

#include <gtest/gtest.h>

TEST(WorldManagerTest, GetAllJobs)
{
    WorldManager worldManager;
    auto const& jobs = worldManager.getAllJobs();
    ASSERT_FALSE(jobs.empty());
}

TEST(WorldManagerTest, GetJob)
{
    WorldManager worldManager;
    auto const& jobs = worldManager.getAllJobs();

    for (auto const& job : jobs)
    {
        auto const* retrievedJob = worldManager.getJob(job->getID());
        ASSERT_EQ(job.get(), retrievedJob);
    }

    auto const* invalidJob = worldManager.getJob(999);
    ASSERT_EQ(nullptr, invalidJob);
}

TEST(WorldManagerTest, MoveJob) {
    WorldManager worldManager;
    auto const& allJobs = worldManager.getAllJobs();
    auto const jobsBeforeMoveSize = allJobs.size();
    ASSERT_FALSE(allJobs.empty());

    const auto jobToMoveId = allJobs.front()->getID();
    auto movedJob = worldManager.moveJob(jobToMoveId);

    ASSERT_EQ(jobToMoveId, movedJob.get()->getID());

    auto const jobsAfterMoveSize = allJobs.size();
    ASSERT_EQ(jobsBeforeMoveSize - 1, jobsAfterMoveSize);

    const auto* movedJobInList = worldManager.getJob(jobToMoveId);
    ASSERT_EQ(nullptr, movedJobInList);
}

TEST(WorldManagerTest, AddNewRandomJob)
{
    WorldManager worldManager;
    auto const jobsBeforeAdditionSize = worldManager.getAllJobs().size();

    worldManager.addNewRandomJob();

    auto const jobsAfterAdditionSize = worldManager.getAllJobs().size();
    ASSERT_EQ(jobsBeforeAdditionSize + 1, jobsAfterAdditionSize);
}

TEST(WorldManagerTest, RemoveRandomJob)
{
    WorldManager worldManager;
    auto const jobsBeforeRemovalSize = worldManager.getAllJobs().size();
    worldManager.removeRandomJob();
    auto const jobsAfterRemovalSize = worldManager.getAllJobs().size();
    ASSERT_EQ(jobsBeforeRemovalSize - 1, jobsAfterRemovalSize);
}
