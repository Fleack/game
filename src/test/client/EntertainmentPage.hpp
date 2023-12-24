#pragma once

#include "../../client/EntertainmentPage.hpp"

#include <QVBoxLayout>

#include <QtTest/QtTest>

class TestEntertainmentPage final : public QObject
{
    Q_OBJECT

private slots:
    static void testInitialization()
    {
        EntertainmentPage const entertainmentPage;

        QVERIFY(entertainmentPage.findChild<QVBoxLayout*>() != nullptr);
        QVERIFY(entertainmentPage.findChild<QLabel*>("descriptionLabel") != nullptr);
        QVERIFY(entertainmentPage.findChild<QPushButton*>("entertainButton") != nullptr);
        QVERIFY(entertainmentPage.findChild<QPushButton*>("backButton") != nullptr);
    }

    static void testBackButtonClicked()
    {
        EntertainmentPage const entertainmentPage;

        QSignalSpy const backSpy(&entertainmentPage, SIGNAL(backToPlayerPageClicked()));

        auto* backButton = entertainmentPage.findChild<QPushButton*>("backButton");
        QVERIFY(backButton != nullptr);
        QTest::mouseClick(backButton, Qt::LeftButton);

        QCOMPARE(backSpy.count(), 1);
    }
};
