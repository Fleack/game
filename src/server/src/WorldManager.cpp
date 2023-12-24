#include "WorldManager.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>

std::array<std::string, 20> const COMPANY_NAMES = {
    "Quantum", "Nova", "Pinnacle", "Zenith", "Stratosphere",
    "Vortex", "Apex", "Spectrum", "Celestial", "Nebula",
    "Aurora", "Stellar", "Eclipse", "Paragon", "Radiant",
    "Abyssal", "Horizon", "Elysian", "Pantheon", "Mystic"};

std::array<std::string, 20> const PROFESSIONS = {
    "Software Developer", "Data Scientist", "Project Manager", "Marketing Specialist",
    "Financial Analyst", "Network Administrator", "Graphic Designer", "Plumber",
    "Sales Representative", "Research Scientist", "Chef", "Medical Doctor",
    "Teacher", "Engineer", "Architect", "Customer Support Specialist",
    "Photographer", "Journalist", "Electrician", "Human Resources Manager"};

WorldManager::WorldManager()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(3, 6);
    for (int i = 0; i < dist(gen); ++i)
    {
        m_jobs.emplace_back(generateRandomJob());
    }
}

std::vector<WorldManager::job_t> const& WorldManager::getAllJobs() const noexcept
{
    std::cout << "getAllJobs";
    return m_jobs;
}

JobActivity const* WorldManager::getJob(uint32_t jobId) const noexcept
{
    auto const it =
        std::ranges::find_if(m_jobs, [jobId](auto const& vacancy) { return vacancy->getID() == jobId; });

    if (it != m_jobs.end())
    {
        return it->get();
    }
    std::cout << "Incorrect job ID: " << jobId;
    return nullptr;
}

std::unique_ptr<JobActivity> WorldManager::moveJob(uint32_t jobId)
{
    auto const it = std::ranges::find_if(m_jobs, [jobId](auto const& vacancy) {
        return vacancy->getID() == jobId;
    });

    if (it != m_jobs.end())
    {
        auto movedJob = std::move(*it);
        m_jobs.erase(it);
        return movedJob;
    }

    std::cout << "Incorrect job ID: " << jobId;
    return nullptr;
}

void WorldManager::addNewRandomJob()
{
    auto job = generateRandomJob();
    std::cout << "Add new random job: " << job->getName() << " [" << job->getID() << "]";
    m_jobs.push_back(std::move(job));
}

void WorldManager::removeRandomJob()
{
    if (m_jobs.empty())
    {
        std::cout << "Trying to remove job from empty vector";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, m_jobs.size() - 1);

    size_t const indexToRemove = dist(gen);
    std::cout << "Removed job: " << m_jobs[indexToRemove]->getName() << " [" << m_jobs[indexToRemove]->getID() << "]";
    m_jobs.erase(m_jobs.begin() + indexToRemove);
}

std::unique_ptr<JobActivity> WorldManager::generateRandomJob()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist1(10, 20); //-V525
    std::uniform_int_distribution<size_t> dist2(5, 10);
    std::uniform_int_distribution<size_t> dist3(0, COMPANY_NAMES.size() - 1);
    std::uniform_int_distribution<size_t> dist4(0, PROFESSIONS.size() - 1);

    uint32_t salaryMin = 250;
    uint32_t salaryMax = 5000;
    uint8_t energyDecrease = dist1(gen);
    uint8_t healthDecrease = dist2(gen);
    uint8_t happienesDecrease = dist2(gen);

    std::string jobName = COMPANY_NAMES[dist3(gen)] + ": " + PROFESSIONS[dist4(gen)];
    return std::make_unique<JobActivity>(std::move(jobName), salaryMin, salaryMax, energyDecrease, healthDecrease, happienesDecrease);
}
