// mainwindow.cpp
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    mainMenuPage = new MainMenuPage(this);
    createPlayerPage = new CreatePlayerPage(this);
    playerPage = nullptr;
    skillsPage = nullptr;

    connect(mainMenuPage, &MainMenuPage::newGameClicked, this, &MainWindow::onNewGameClicked);
    connect(mainMenuPage, &MainMenuPage::exitClicked, this, &MainWindow::onExitClicked);

    connect(createPlayerPage, &CreatePlayerPage::backClicked, this, &MainWindow::onBackClicked);
    connect(createPlayerPage, &CreatePlayerPage::createPlayerClicked, this, &MainWindow::onCreatePlayerClicked);

    setCentralWidget(mainMenuPage);
}

void MainWindow::onNewGameClicked()
{
    delete playerPage;
    delete skillsPage;

    createPlayerPage = new CreatePlayerPage(this);
    connect(createPlayerPage, &CreatePlayerPage::backClicked, this, &MainWindow::onBackClicked);
    connect(createPlayerPage, &CreatePlayerPage::createPlayerClicked, this, &MainWindow::onCreatePlayerClicked);

    setCentralWidget(createPlayerPage);
}

void MainWindow::onExitClicked()
{
    close();
}

void MainWindow::onBackClicked()
{
    setCentralWidget(mainMenuPage);
}

void MainWindow::onCreatePlayerClicked(const QString& playerName)
{
    delete playerPage;
    delete skillsPage;

    playerPage = new PlayerPage(playerName, this);
    connect(playerPage, &PlayerPage::backToMainMenuClicked, this, &MainWindow::onBackClicked);
    connect(playerPage, &PlayerPage::skillsClicked, this, &MainWindow::onSkillsClicked);

    setCentralWidget(playerPage);
}


void MainWindow::onSkillsClicked()
{
    showSkillsPage();
}

void MainWindow::showSkillsPage()
{
    delete skillsPage;

    skillsPage = new PlayerSkillsPage(this);
    connect(skillsPage, &PlayerSkillsPage::backToMainMenuClicked, this, &MainWindow::onBackClicked);

    setCentralWidget(skillsPage);
}
