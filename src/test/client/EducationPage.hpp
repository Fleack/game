#pragma once

#include "../../client/EducationPage.hpp"

#include <QVBoxLayout>

#include <QtTest/QtTest>

class TestEducationPage final : public QObject
{
    Q_OBJECT

private slots:
    static void testInitialization()
    {
        EducationPage const educationPage;

        QVERIFY(educationPage.findChild<QVBoxLayout*>() != nullptr);
        QVERIFY(educationPage.findChild<QLabel*>("descriptionLabel") != nullptr);
        QVERIFY(educationPage.findChild<QPushButton*>("buyAndLearnButton") != nullptr);
        QVERIFY(educationPage.findChild<QPushButton*>("backButton") != nullptr);
    }

    static void testBackButtonClicked()
    {
        EducationPage const educationPage;

        QSignalSpy const backSpy(&educationPage, SIGNAL(backToPlayerPageClicked()));

        auto* backButton = educationPage.findChild<QPushButton*>("backButton");
        QVERIFY(backButton != nullptr);
        QTest::mouseClick(backButton, Qt::LeftButton);

        QCOMPARE(backSpy.count(), 1);
    }
};
