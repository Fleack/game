// mainwindow.hpp
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "PlayerSkillsPage.hpp"
#include "CreatePlayerPage.hpp"
#include "MainMenuPage.hpp"
#include "PlayerPage.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void onNewGameClicked();
    void onExitClicked();
    void onBackClicked();
    void onCreatePlayerClicked(QString const& playerName);
    void onSkillsClicked();

private:
    void showSkillsPage();

private:
    MainMenuPage* mainMenuPage;
    CreatePlayerPage* createPlayerPage;
    PlayerPage* playerPage;
    PlayerSkillsPage* skillsPage;
};

#endif // MAINWINDOW_HPP
