// jobspage.cpp
#include "JobsPage.hpp"

#include <QDebug>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

JobsPage::JobsPage(QWidget* parent)
    : QWidget(parent)
    , networkManager(new QNetworkAccessManager(this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QTableWidget* jobsTable = new QTableWidget(this);
    jobsTable->setObjectName("jobsTable");
    jobsTable->setColumnCount(7); // Добавлен столбец для кнопки "Устроиться"
    jobsTable->setHorizontalHeaderLabels({"ID", "Название", "Зарплата", "РАсход энергии", "Упадоч счастья", "Happiness Decrease", "Действия"});
    jobsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPushButton* backButton = new QPushButton("Назад", this);

    layout->addWidget(jobsTable);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &JobsPage::onBackClicked);

    fetchJobs();
}

void JobsPage::onBackClicked()
{
    emit backToPlayerPageClicked();
}

void JobsPage::fetchJobs()
{
    // Отправка запроса на сервер с command = "get_jobs"
    QNetworkRequest request(QUrl("http://localhost:12345")); // Замените на ваш URL сервера
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "get_jobs";

    QJsonDocument requestData(requestBody);
    QByteArray requestDataBytes = requestData.toJson();

    QNetworkReply* reply = networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
            processJobs(jsonDocument);
        }
        else
        {
            qDebug() << "Error fetching jobs:" << reply->errorString();
        }

        reply->deleteLater();
    });
}

void JobsPage::processJobs(QJsonDocument const& jsonDocument)
{
    QTableWidget* jobsTable = findChild<QTableWidget*>("jobsTable");

    if (jobsTable && jsonDocument.isObject())
    {
        QJsonObject jsonObject = jsonDocument.object();
        QJsonArray jobsArray = jsonObject["jobs"].toArray();

        jobsTable->clearContents();

        for (QJsonValue const& jobValue : jobsArray)
        {
            QJsonObject jobObject = jobValue.toObject();
            int id = jobObject["id"].toInt();
            QString name = jobObject["name"].toString();
            int salary = jobObject["salary"].toInt();
            int energyDecrease = jobObject["energy_decrease"].toInt();
            int healthDecrease = jobObject["health_decrease"].toInt();
            int happinessDecrease = jobObject["happiness_decrease"].toInt();

            int row = jobsTable->rowCount();
            jobsTable->insertRow(row);
            jobsTable->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
            jobsTable->setItem(row, 1, new QTableWidgetItem(name));
            jobsTable->setItem(row, 2, new QTableWidgetItem(QString::number(salary)));
            jobsTable->setItem(row, 3, new QTableWidgetItem(QString::number(energyDecrease)));
            jobsTable->setItem(row, 4, new QTableWidgetItem(QString::number(healthDecrease)));
            jobsTable->setItem(row, 5, new QTableWidgetItem(QString::number(happinessDecrease)));

            QPushButton* applyJobButton = new QPushButton("Устроиться", this);
            connect(applyJobButton, &QPushButton::clicked, [this, id]() {
                onApplyJobClicked(id);
            });

            jobsTable->setCellWidget(row, 6, applyJobButton);
        }
    }
}

void JobsPage::onApplyJobClicked(int jobId)
{
    // Отправка запроса на сервер с command = "apply_job" и полем job_id = ид_работы
    QNetworkRequest request(QUrl("http://localhost:12345")); // Замените на ваш URL сервера
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "apply_job";
    requestBody["job_id"] = jobId;

    QJsonDocument requestData(requestBody);
    QByteArray requestDataBytes = requestData.toJson();

    QNetworkReply* reply = networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            // Обработка успешного ответа (если необходимо)
            qDebug() << "Successfully applied for job";
        } else {
            qDebug() << "Error applying for job:" << reply->errorString();
        }

        reply->deleteLater();
    });
}
