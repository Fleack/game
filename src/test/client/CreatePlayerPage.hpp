#pragma once

#include "../../client/CreatePlayerPage.hpp"

#include <QtTest/QtTest>

class TestCreatePlayerPage final : public QObject
{
    Q_OBJECT

private slots:
    static void testInitialization()
    {
        CreatePlayerPage const createPlayerPage;

        QVERIFY(createPlayerPage.findChild<QLineEdit*>() != nullptr);
        QVERIFY(createPlayerPage.findChild<QPushButton*>("Создатьg") != nullptr);
        QVERIFY(createPlayerPage.findChild<QPushButton*>("Назад") != nullptr);
    }

    static void testBackButtonClicked()
    {
        CreatePlayerPage const createPlayerPage;

        QSignalSpy const backButtonSpy(&createPlayerPage, SIGNAL(backClicked()));

        auto* backButton = createPlayerPage.findChild<QPushButton*>("Назад");
        QVERIFY(backButton != nullptr);
        QTest::mouseClick(backButton, Qt::LeftButton);

        QCOMPARE(backButtonSpy.count(), 1);
    }
};
