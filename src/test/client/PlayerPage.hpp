#pragma once

#include "../../client/PlayerPage.hpp"

#include <QtTest/QtTest>

class TestPlayerPage final : public QObject
{
    Q_OBJECT

private slots:
    static void testInitialization()
    {
        PlayerPage const playerPage;

        QVERIFY(playerPage.findChild<QVBoxLayout*>() != nullptr);
        QVERIFY(playerPage.findChild<QPushButton*>("Работа") != nullptr);
        QVERIFY(playerPage.findChild<QPushButton*>("Умения") != nullptr);
        QVERIFY(playerPage.findChild<QPushButton*>("Развлечения") != nullptr);
        QVERIFY(playerPage.findChild<QPushButton*>("Обучение") != nullptr);
        QVERIFY(playerPage.findChild<QPushButton*>("Назад") != nullptr);
        QVERIFY(playerPage.findChild<QPushButton*>("Следующий год") != nullptr);
    }

    static void testNavigationButtonsClicked()
    {
        PlayerPage playerPage;

        QSignalSpy jobsSpy(&playerPage, SIGNAL(jobsClicked()));
        QSignalSpy skillsSpy(&playerPage, SIGNAL(skillsClicked()));
        QSignalSpy entertainmentSpy(&playerPage, SIGNAL(entertainmentClicked()));
        QSignalSpy educationSpy(&playerPage, SIGNAL(educationClicked()));

        auto* jobsButton = playerPage.findChild<QPushButton*>("Работа");
        auto* skillsButton = playerPage.findChild<QPushButton*>("Умения");
        auto* entertainmentButton = playerPage.findChild<QPushButton*>("Развлечения");
        auto* educationButton = playerPage.findChild<QPushButton*>("Обучение");

        QVERIFY(jobsButton != nullptr);
        QVERIFY(skillsButton != nullptr);
        QVERIFY(entertainmentButton != nullptr);
        QVERIFY(educationButton != nullptr);

        QTest::mouseClick(jobsButton, Qt::LeftButton);
        QTest::mouseClick(skillsButton, Qt::LeftButton);
        QTest::mouseClick(entertainmentButton, Qt::LeftButton);
        QTest::mouseClick(educationButton, Qt::LeftButton);

        QCOMPARE(jobsSpy.count(), 1);
        QCOMPARE(skillsSpy.count(), 1);
        QCOMPARE(entertainmentSpy.count(), 1);
        QCOMPARE(educationSpy.count(), 1);
    }
};
