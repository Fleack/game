// mainwindow.cpp
#include "MainWindow.hpp"

#include "JobsPage.hpp"

// TODO REWORK SLOTS AND METHODS
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
{
    auto* mainMenuPage = new MainMenuPage(this);

    connect(mainMenuPage, &MainMenuPage::newGameClicked, this, &MainWindow::onNewGameClicked);
    connect(mainMenuPage, &MainMenuPage::exitClicked, this, &MainWindow::onExitClicked);

    setCentralWidget(mainMenuPage);
}

void MainWindow::onNewGameClicked()
{
    auto* createPlayerPage = new CreatePlayerPage(this);
    connect(createPlayerPage, &CreatePlayerPage::backClicked, this, &MainWindow::onBackToMainMenuClicked);
    connect(createPlayerPage, &CreatePlayerPage::createPlayerClicked, this, &MainWindow::onCreatePlayerClicked);

    setCentralWidget(createPlayerPage);
}

void MainWindow::onBackToMainMenuClicked()
{
    auto* mainMenuPage = new MainMenuPage(this);
    connect(mainMenuPage, &MainMenuPage::newGameClicked, this, &MainWindow::onNewGameClicked);
    connect(mainMenuPage, &MainMenuPage::exitClicked, this, &MainWindow::onExitClicked);
    setCentralWidget(mainMenuPage);
}

void MainWindow::onCreatePlayerClicked()
{
    auto* playerPage = new PlayerPage(this);
    connect(playerPage, &PlayerPage::backToMainMenuClicked, this, &MainWindow::onBackToMainMenuClicked);
    connect(playerPage, &PlayerPage::skillsClicked, this, &MainWindow::onSkillsClicked);
    connect(playerPage, &PlayerPage::jobsClicked, this, &MainWindow::onJobsClicked);

    setCentralWidget(playerPage);
}

void MainWindow::onSkillsClicked()
{
    auto* skillsPage = new PlayerSkillsPage(this);
    connect(skillsPage, &PlayerSkillsPage::backToPlayerPageClicked, this, &MainWindow::onCreatePlayerClicked);

    setCentralWidget(skillsPage);
}

void MainWindow::onJobsClicked()
{
    auto* jobsPage = new JobsPage(this);
    connect(jobsPage, &JobsPage::backToPlayerPageClicked, this, &MainWindow::onCreatePlayerClicked);

    setCentralWidget(jobsPage);
}

void MainWindow::onExitClicked()
{
    close();
}
