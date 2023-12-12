#include "WorldManager.hpp"

#include <iostream>
#include <algorithm>
#include <functional>
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
    srand(time(nullptr));
    // Generate from 3 to 12 random jobs
    for (int i = 0; i < 3 + rand() % 10; ++i)
    {
        m_jobs.emplace_back(generateRandomJob());
    }
}

std::vector<WorldManager::job_t> const& WorldManager::getAllJobs() const noexcept
{
    std::cout << "getAllJobs";
    return m_jobs;
}

JobActivity const* WorldManager::getJob(uint8_t jobId) const noexcept
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

std::unique_ptr<JobActivity> WorldManager::moveJob(uint8_t jobId)
{
    auto const it = std::ranges::remove_if(m_jobs, [jobId](auto const& vacancy) {
        return vacancy->getID() == jobId;
    }).begin();

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
    uint32_t salaryMin = 250;
    uint32_t salaryMax = 5000;
    uint8_t energyDecrease = 10 + std::rand() % 10;
    uint8_t healthDecrease = 5 + std::rand() % 5;
    uint8_t happienesDecrease = 5 + std::rand() % 5;

    std::string jobName = COMPANY_NAMES[std::rand() % COMPANY_NAMES.size()];
    +": " + PROFESSIONS[std::rand() % PROFESSIONS.size()];
    return std::make_unique<JobActivity>(std::move(jobName), salaryMin, salaryMax, energyDecrease, healthDecrease, happienesDecrease);
}
