#pragma once

#include "CreatePlayerPage.hpp"
#include "PlayerPage.hpp"

#include <QMainWindow>

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

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
    static void terminateServer();
};
