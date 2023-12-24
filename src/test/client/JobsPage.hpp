#pragma once

#include "../../client/JobsPage.hpp"

#include <QVBoxLayout>

#include <QtTest/QtTest>

class TestJobsPage final : public QObject
{
    Q_OBJECT

private slots:
    static void testInitialization()
    {
        JobsPage const jobsPage;

        QVERIFY(jobsPage.findChild<QVBoxLayout*>() != nullptr);
        QVERIFY(jobsPage.findChild<QTableWidget*>("jobsTable") != nullptr);
        QVERIFY(jobsPage.findChild<QLabel*>("jobDescriptionLabel") != nullptr);
        QVERIFY(jobsPage.findChild<QPushButton*>("workButton") != nullptr);
        QVERIFY(jobsPage.findChild<QPushButton*>("quitJobButton") != nullptr);
        QVERIFY(jobsPage.findChild<QPushButton*>("backButton") != nullptr);
    }

    static void testBackButtonClicked()
    {
        JobsPage const jobsPage;

        QSignalSpy const backSpy(&jobsPage, SIGNAL(backToPlayerPageClicked()));

        auto* backButton = jobsPage.findChild<QPushButton*>("backButton");
        QVERIFY(backButton != nullptr);
        QTest::mouseClick(backButton, Qt::LeftButton);

        QCOMPARE(backSpy.count(), 1);
    }

    static void testProcessJobs()
    {
        JobsPage jobsPage;

        QJsonObject testData;
        testData["jobs"] = QJsonArray{
            QJsonObject{
                {"id", 1},
                {"name", "Job 1"},
                {"salary", 100},
                {"energy_decrease", 10},
                {"health_decrease", 5},
                {"happiness_decrease", 2},
            },
            QJsonObject{
                {"id", 2},
                {"name", "Job 2"},
                {"salary", 200},
                {"energy_decrease", 20},
                {"health_decrease", 10},
                {"happiness_decrease", 4},
            },
        };

        QJsonDocument const jsonDocument(testData);

        jobsPage.processJobs(jsonDocument);

        auto const* jobsTable = jobsPage.findChild<QTableWidget*>("jobsTable");
        QVERIFY(jobsTable != nullptr);
        QCOMPARE(jobsTable->rowCount(), 2);
        QCOMPARE(jobsTable->columnCount(), 6);
        QCOMPARE(jobsTable->horizontalHeaderItem(0)->text(), QString("Название"));
        QCOMPARE(jobsTable->horizontalHeaderItem(1)->text(), QString("Зарплата"));
        QCOMPARE(jobsTable->horizontalHeaderItem(2)->text(), QString("Расход энергии"));
        QCOMPARE(jobsTable->horizontalHeaderItem(3)->text(), QString("Упадок здоровья"));
        QCOMPARE(jobsTable->horizontalHeaderItem(4)->text(), QString("Упадок счастья"));
        QCOMPARE(jobsTable->horizontalHeaderItem(5)->text(), QString("Действия"));

        QCOMPARE(jobsTable->item(0, 0)->text(), QString("Job 1"));
        QCOMPARE(jobsTable->item(0, 1)->text(), QString("100"));
        QCOMPARE(jobsTable->item(0, 2)->text(), QString("10"));
        QCOMPARE(jobsTable->item(0, 3)->text(), QString("5"));
        QCOMPARE(jobsTable->item(0, 4)->text(), QString("2"));

        QCOMPARE(jobsTable->item(1, 0)->text(), QString("Job 2"));
        QCOMPARE(jobsTable->item(1, 1)->text(), QString("200"));
        QCOMPARE(jobsTable->item(1, 2)->text(), QString("20"));
        QCOMPARE(jobsTable->item(1, 3)->text(), QString("10"));
        QCOMPARE(jobsTable->item(1, 4)->text(), QString("4"));

        auto const* applyJobButton1 = qobject_cast<QPushButton*>(jobsTable->cellWidget(0, 5));
        auto const* applyJobButton2 = qobject_cast<QPushButton*>(jobsTable->cellWidget(1, 5));

        QVERIFY(applyJobButton1 != nullptr);
        QVERIFY(applyJobButton2 != nullptr);
    }
};
