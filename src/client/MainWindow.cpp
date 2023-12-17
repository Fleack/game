// mainwindow.cpp
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    mainMenuPage = new MainMenuPage(this);
    createPlayerPage = new CreatePlayerPage(this);
    characterPage = nullptr;

    connect(mainMenuPage, &MainMenuPage::newGameClicked, this, &MainWindow::onNewGameClicked);
    connect(mainMenuPage, &MainMenuPage::exitClicked, this, &MainWindow::onExitClicked);

    connect(createPlayerPage, &CreatePlayerPage::backClicked, this, &MainWindow::onBackClicked);
    connect(createPlayerPage, &CreatePlayerPage::createPlayerClicked, this, &MainWindow::onCreatePlayerClicked);

    setCentralWidget(mainMenuPage);
}

void MainWindow::onNewGameClicked()
{
    delete characterPage;

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

void MainWindow::onCreatePlayerClicked(QString const& playerName)
{
    delete characterPage;

    characterPage = new CharacterPage(playerName, this);
    connect(characterPage, &CharacterPage::backToMainMenuClicked, this, &MainWindow::onBackClicked); // sigsegv
    setCentralWidget(characterPage);
}
