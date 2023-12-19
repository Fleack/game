// mainwindow.hpp
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "CreatePlayerPage.hpp"
#include "MainMenuPage.hpp"
#include "PlayerPage.hpp"
#include "PlayerSkillsPage.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onNewGameClicked();
    void onExitClicked();
    void onBackToMainMenuClicked();
    void onCreatePlayerClicked();
    void onSkillsClicked();
    void onJobsClicked();
    void onEntertainmentClicked();
    void onEducationClicked();
    void terminateServer();
};

#endif // MAINWINDOW_HPP
