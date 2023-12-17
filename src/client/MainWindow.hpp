// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CharacterPage.hpp"
#include "CreatePlayerPage.hpp"
#include "MainMenuPage.hpp"

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

private:
    MainMenuPage* mainMenuPage;
    CreatePlayerPage* createPlayerPage;
    CharacterPage* characterPage;
};

#endif // MAINWINDOW_H
