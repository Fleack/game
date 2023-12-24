#pragma once

#include "src/PlayerSkillsPage.hpp"

#include <QtTest/QtTest>

class TestPlayerSkillsPage final : public QObject
{
    Q_OBJECT

private slots:
    static void testInitialization()
    {
        PlayerSkillsPage const playerSkillsPage;

        QVERIFY(playerSkillsPage.findChild<QVBoxLayout*>() != nullptr);
        QVERIFY(playerSkillsPage.findChild<QTableWidget*>("skillsTable") != nullptr);
        QVERIFY(playerSkillsPage.findChild<QPushButton*>("backButton") != nullptr);
    }

    static void testBackButtonClicked()
    {
        PlayerSkillsPage const playerSkillsPage;

        QSignalSpy const backSpy(&playerSkillsPage, SIGNAL(backToPlayerPageClicked()));

        auto* backButton = playerSkillsPage.findChild<QPushButton*>("backButton");
        QVERIFY(backButton != nullptr);
        QTest::mouseClick(backButton, Qt::LeftButton);

        QCOMPARE(backSpy.count(), 1);
    }
};
