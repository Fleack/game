// jobspage.cpp
#include "JobsPage.hpp"

#include <QDebug>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
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
    jobsTable->setColumnCount(7);
    jobsTable->setHorizontalHeaderLabels({"ID", "Название", "Зарплата", "Расход энергии", "Упадок здоровья", "Happiness Decrease", "Действия"});
    jobsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QLabel* jobDescriptionLabel = new QLabel(this);
    jobDescriptionLabel->setObjectName("jobDescriptionLabel");

    QPushButton* quitJobButton = new QPushButton("Уволиться", this);
    quitJobButton->setObjectName("quitJobButton");

    QPushButton* backButton = new QPushButton("Назад", this);
    backButton->setObjectName("backButton");

    QPushButton* workButton = new QPushButton("Работать", this);
    workButton->setObjectName("workButton");

    layout->addWidget(jobsTable);
    layout->addWidget(jobDescriptionLabel);
    layout->addWidget(workButton);  // Make sure to add the "Работать" button to the layout
    layout->addWidget(quitJobButton);
    layout->addWidget(backButton);

    connect(quitJobButton, &QPushButton::clicked, this, &JobsPage::onQuitJobClicked);
    connect(backButton, &QPushButton::clicked, this, &JobsPage::onBackClicked);
    connect(workButton, &QPushButton::clicked, this, &JobsPage::onWorkClicked);

    fetchJobs();
    fetchPlayerJob();
}

void JobsPage::onBackClicked()
{
    emit backToPlayerPageClicked();
}

void JobsPage::fetchJobs()
{
    QNetworkRequest request(QUrl("http://localhost:12345"));
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

        hideQuitJobButton(true);

        reply->deleteLater();
    });
}

void JobsPage::processJobs(QJsonDocument const& jsonDocument)
{
    QTableWidget* jobsTable = findChild<QTableWidget*>("jobsTable");
    QPushButton* workButton = findChild<QPushButton*>("workButton");

    hideQuitJobButton(true);
    workButton->setVisible(false);


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
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "apply_job";
    requestBody["job_id"] = jobId;

    QJsonDocument requestData(requestBody);
    QByteArray requestDataBytes = requestData.toJson();

    QNetworkReply* reply = networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            qDebug() << "Successfully applied for job";

            fetchPlayerJob();
        }
        else
        {
            qDebug() << "Error applying for job:" << reply->errorString();
        }

        reply->deleteLater();
    });
}

void JobsPage::fetchPlayerJob()
{
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "get_player_job";

    QJsonDocument requestData(requestBody);
    QByteArray requestDataBytes = requestData.toJson();

    QNetworkReply* reply = networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
            processPlayerJob(jsonDocument);
        }
        else
        {
            qDebug() << "Error fetching player job:" << reply->errorString();
        }

        reply->deleteLater();
    });
}

void JobsPage::processPlayerJob(QJsonDocument const& jsonDocument)
{
    QTableWidget* jobsTable = findChild<QTableWidget*>("jobsTable");
    QLabel* jobDescriptionLabel = findChild<QLabel*>("jobDescriptionLabel");
    QPushButton* workButton = findChild<QPushButton*>("workButton");

    if (jobsTable && jobDescriptionLabel && workButton && jsonDocument.isObject())
    {
        QJsonObject jsonObject = jsonDocument.object();

        if (jsonObject.contains("job"))
        {
            QJsonObject jobObject = jsonObject["job"].toObject();
            QString name = jobObject["name"].toString();
            int salary = jobObject["salary"].toInt();
            int energyDecrease = jobObject["energy_decrease"].toInt();
            int healthDecrease = jobObject["health_decrease"].toInt();
            int happinessDecrease = jobObject["happiness_decrease"].toInt();

            jobsTable->setVisible(false);

            QString jobDescription = QString("Название: %1\nЗарплата: %2\n"
                                             "Расход энергии: %3\nУпадок здоровья: %4\n"
                                             "Упадок счастья: %5")
                                         .arg(name)
                                         .arg(salary)
                                         .arg(energyDecrease)
                                         .arg(healthDecrease)
                                         .arg(happinessDecrease);

            jobDescriptionLabel->setText(jobDescription);
            jobDescriptionLabel->setVisible(true);
            hideQuitJobButton(false);

            workButton->setVisible(true);
        }
        else
        {
            jobDescriptionLabel->setVisible(false);
            jobsTable->setVisible(true);
            hideQuitJobButton(true);

            workButton->setVisible(false);
        }
    }
}

void JobsPage::onQuitJobClicked()
{
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "quit_job";

    QJsonDocument requestData(requestBody);
    QByteArray requestDataBytes = requestData.toJson();

    QNetworkReply* reply = networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            qDebug() << "Successfully quit job";

            // Instead of fetching jobs immediately, update the UI to show the vacancies table
            showVacanciesTable();
        }
        else
        {
            qDebug() << "Error quitting job:" << reply->errorString();
        }

        reply->deleteLater();
    });
}

void JobsPage::showVacanciesTable()
{
    QTableWidget* jobsTable = findChild<QTableWidget*>("jobsTable");
    QLabel* jobDescriptionLabel = findChild<QLabel*>("jobDescriptionLabel");

    if (jobsTable && jobDescriptionLabel)
    {
        jobsTable->clearContents();
        jobsTable->setRowCount(0);

        fetchJobs();

        jobDescriptionLabel->setVisible(false);
        jobsTable->setVisible(true);

        hideQuitJobButton(true);
    }
}

void JobsPage::hideQuitJobButton(bool hide)
{
    QPushButton* quitJobButton = findChild<QPushButton*>("quitJobButton");

    if (quitJobButton)
        quitJobButton->setVisible(!hide);
}

void JobsPage::onWorkClicked()
{
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "perform_job";

    QJsonDocument requestData(requestBody);
    QByteArray requestDataBytes = requestData.toJson();

    QNetworkReply* reply = networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            qDebug() << "Successfully performed job";
        }
        else
        {
            qDebug() << "Error performing job:" << reply->errorString();
        }

        reply->deleteLater();
    });
}
