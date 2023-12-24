#pragma once

#include "Activities/JobActivity.hpp"

#include <memory>
#include <vector>

class WorldManager
{
public:
    using job_t = std::unique_ptr<JobActivity>;
    WorldManager();

    std::vector<job_t> const& getAllJobs() const noexcept;
    JobActivity const* getJob(uint32_t /* jobId */) const noexcept;
    std::unique_ptr<JobActivity> moveJob(uint32_t /* jobId */);

    void addNewRandomJob();
    void removeRandomJob();

private:
    static std::unique_ptr<JobActivity> generateRandomJob();

private:
    std::vector<job_t> m_jobs;
};
