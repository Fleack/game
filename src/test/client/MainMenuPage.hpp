#pragma once

#include "../../client/MainMenuPage.hpp"

#include <QVBoxLayout>

#include <QtTest/QtTest>

class TestMainMenuPage final : public QObject
{
    Q_OBJECT

private slots:
    static void testInitialization()
    {
        MainMenuPage const mainMenuPage;

        QVERIFY(mainMenuPage.findChild<QVBoxLayout*>() != nullptr);
        QVERIFY(mainMenuPage.findChild<QPushButton*>("Новая игра") != nullptr);
        QVERIFY(mainMenuPage.findChild<QPushButton*>("Выход") != nullptr);
    }

    static void testNewGameButtonClicked()
    {
        MainMenuPage const mainMenuPage;

        QSignalSpy const newGameSpy(&mainMenuPage, SIGNAL(newGameClicked()));

        auto* newGameButton = mainMenuPage.findChild<QPushButton*>("Новая игра");
        QVERIFY(newGameButton != nullptr);
        QTest::mouseClick(newGameButton, Qt::LeftButton);

        QCOMPARE(newGameSpy.count(), 1);
    }

    static void testExitButtonClicked()
    {
        MainMenuPage const mainMenuPage;

        QSignalSpy const exitSpy(&mainMenuPage, SIGNAL(exitClicked()));

        auto* exitButton = mainMenuPage.findChild<QPushButton*>("Выход");
        QVERIFY(exitButton != nullptr);
        QTest::mouseClick(exitButton, Qt::LeftButton);

        QCOMPARE(exitSpy.count(), 1);
    }
};
