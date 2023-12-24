#include "CreatePlayerPage.hpp"
#include "EducationPage.hpp"
#include "EntertainmentPage.hpp"
#include "JobsPage.hpp"
#include "MainMenuPage.hpp"
#include "PlayerPage.hpp"
#include "PlayerSkillsPage.hpp"

#include <QApplication>
#include <QTest>
#include <iostream>

void printColoredMessage(const std::string& message, bool success)
{
    if (success)
        std::cout << "\033[1;32m" << message << " passed\033[0m\n" << std::endl;
    else
        std::cout << "\033[1;31m" << message << " failed\033[0m\n" << std::endl;
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv); // -V808

    TestCreatePlayerPage testCreatePlayerPage;
    TestEducationPage testEducationPage;
    TestEntertainmentPage testEntertainmentPage;
    TestJobsPage testJobsPage;
    TestMainMenuPage testMainMenuPage;
    TestPlayerPage testPlayerPage;
    TestPlayerSkillsPage testPlayerSkillsPage;

    int result = 0;

    result |= QTest::qExec(&testCreatePlayerPage, argc, argv);
    printColoredMessage("CreatePlayerPage tests", result == 0);

    int resultEducation = QTest::qExec(&testEducationPage, argc, argv);
    printColoredMessage("EducationPage tests", resultEducation == 0);
    result |= resultEducation;

    int resultEntertainment = QTest::qExec(&testEntertainmentPage, argc, argv);
    printColoredMessage("EntertainmentPage tests", resultEntertainment == 0);
    result |= resultEntertainment;

    int resultJobs = QTest::qExec(&testJobsPage, argc, argv);
    printColoredMessage("JobsPage tests", resultJobs == 0);
    result |= resultJobs;

    int resultMainMenu = QTest::qExec(&testMainMenuPage, argc, argv);
    printColoredMessage("MainMenuPage tests", resultMainMenu == 0);
    result |= resultMainMenu;

    int resultPlayer = QTest::qExec(&testPlayerPage, argc, argv);
    printColoredMessage("PlayerPage tests", resultPlayer == 0);
    result |= resultPlayer;

    int resultPlayerSkills = QTest::qExec(&testPlayerSkillsPage, argc, argv);
    printColoredMessage("PlayerSkillsPage tests", resultPlayerSkills == 0);
    result |= resultPlayerSkills;

    if (result)
    {
        std::cout << "\033[1;31mSome tests failed!\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;32mAll tests passed!\033[0m" << std::endl;
    }

    return result;
}
