#include "JobsPage.hpp"

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
    , m_networkManager(new QNetworkAccessManager(this))
{
    auto* layout = new QVBoxLayout(this);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("JobsPage {"
                  "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #2C3E50, stop:1 #34495E);"
                  "}");

    auto* jobsTable = new QTableWidget(this);

    jobsTable->setObjectName("jobsTable");
    jobsTable->setColumnCount(6);
    jobsTable->setHorizontalHeaderLabels({"Название", "Зарплата", "Расход энергии", "Упадок здоровья", "Упадок счастья", "Действия"});
    jobsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto* jobDescriptionLabel = new QLabel(this);

    auto* workButton = new QPushButton("Работать", this);
    auto* quitJobButton = new QPushButton("Уволиться", this);
    auto* backButton = new QPushButton("Назад", this);

    applyLabelStyle(jobDescriptionLabel);
    applyButtonStyle(workButton);
    applyButtonStyle(quitJobButton);
    applyButtonStyle(backButton);

    jobDescriptionLabel->setObjectName("jobDescriptionLabel");
    workButton->setObjectName("workButton");
    quitJobButton->setObjectName("quitJobButton");
    backButton->setObjectName("backButton");

    layout->addWidget(jobsTable);
    layout->addWidget(jobDescriptionLabel, 0, Qt::AlignHCenter);
    layout->addWidget(workButton, 0, Qt::AlignHCenter);
    layout->addWidget(quitJobButton, 0, Qt::AlignHCenter);
    layout->addWidget(backButton, 0, Qt::AlignHCenter);

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

    QJsonDocument const requestData(requestBody);
    QByteArray const requestDataBytes = requestData.toJson();

    QNetworkReply* reply = m_networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            const QByteArray responseData = reply->readAll();
            const QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
            processJobs(jsonDocument);

            auto* jobsTable = findChild<QTableWidget*>("jobsTable");
            if (jobsTable)
            {
                applyTableStyle(jobsTable);
            }
        }

        hideQuitJobButton(true);

        reply->deleteLater();
    });
}

void JobsPage::processJobs(QJsonDocument const& jsonDocument)
{
    auto* jobsTable = findChild<QTableWidget*>("jobsTable");
    auto* workButton = findChild<QPushButton*>("workButton");

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
            int const salary = jobObject["salary"].toInt();
            int const energyDecrease = jobObject["energy_decrease"].toInt();
            int const healthDecrease = jobObject["health_decrease"].toInt();
            int const happinessDecrease = jobObject["happiness_decrease"].toInt();

            int const row = jobsTable->rowCount();
            jobsTable->insertRow(row);

            jobsTable->setItem(row, 0, new QTableWidgetItem(name));
            jobsTable->setItem(row, 1, new QTableWidgetItem(QString::number(salary)));
            jobsTable->setItem(row, 2, new QTableWidgetItem(QString::number(energyDecrease)));
            jobsTable->setItem(row, 3, new QTableWidgetItem(QString::number(healthDecrease)));
            jobsTable->setItem(row, 4, new QTableWidgetItem(QString::number(happinessDecrease)));

            auto* applyJobButton = new QPushButton("Устроиться", this);
            applyJobApplyButtonStyle(applyJobButton);

            connect(applyJobButton, &QPushButton::clicked, [this, id]() {
                onApplyJobClicked(id);
            });

            jobsTable->setCellWidget(row, 5, applyJobButton);
        }
    }
}

void JobsPage::onApplyJobClicked(int const jobId)
{
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "apply_job";
    requestBody["job_id"] = jobId;

    QJsonDocument const requestData(requestBody);
    QByteArray const requestDataBytes = requestData.toJson();

    QNetworkReply* reply = m_networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) { fetchPlayerJob(); }

        reply->deleteLater();
    });
}

void JobsPage::fetchPlayerJob()
{
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "get_player_job";

    QJsonDocument const requestData(requestBody);
    QByteArray const requestDataBytes = requestData.toJson();

    QNetworkReply* reply = m_networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray const responseData = reply->readAll();
            QJsonDocument const jsonDocument = QJsonDocument::fromJson(responseData);
            processPlayerJob(jsonDocument);
        }

        reply->deleteLater();
    });
}

void JobsPage::processPlayerJob(QJsonDocument const& jsonDocument)
{
    auto* jobsTable = findChild<QTableWidget*>("jobsTable");
    auto* jobDescriptionLabel = findChild<QLabel*>("jobDescriptionLabel");
    auto* workButton = findChild<QPushButton*>("workButton");

    if (jobsTable && jobDescriptionLabel && workButton && jsonDocument.isObject())
    {
        QJsonObject jsonObject = jsonDocument.object();

        if (jsonObject.contains("job"))
        {
            createJobDescription(jsonObject, jobDescriptionLabel);
            jobsTable->setVisible(false);
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

    QJsonDocument const requestData(requestBody);
    QByteArray const requestDataBytes = requestData.toJson();

    QNetworkReply* reply = m_networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) { showVacanciesTable(); }

        reply->deleteLater();
    });
}

void JobsPage::showVacanciesTable()
{
    auto* jobsTable = findChild<QTableWidget*>("jobsTable");
    auto* jobDescriptionLabel = findChild<QLabel*>("jobDescriptionLabel");

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

void JobsPage::hideQuitJobButton(bool const hide) const
{
    if (auto* quitJobButton = findChild<QPushButton*>("quitJobButton"))
    {
        quitJobButton->setVisible(!hide);
    }
}

void JobsPage::onWorkClicked()
{
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "perform_job";

    QJsonDocument const requestData(requestBody);
    QByteArray const requestDataBytes = requestData.toJson();

    QNetworkReply* reply = m_networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [reply]() {
        reply->deleteLater();
    });
}

void JobsPage::createJobDescription(QJsonObject const& json, QLabel* jobDescriptionLabel)
{
    QJsonObject jobObject = json["job"].toObject();
    QString const name = jobObject["name"].toString();
    int const salary = jobObject["salary"].toInt();
    int const energyDecrease = jobObject["energy_decrease"].toInt();
    int const healthDecrease = jobObject["health_decrease"].toInt();
    int const happinessDecrease = jobObject["happiness_decrease"].toInt();

    QString const jobDescriptionStyle = "QLabel {"
                                        "    color: white;"
                                        "    padding: 10px;"
                                        "    border-radius: 5px;"
                                        "    font-size: 20px;"
                                        "}";

    jobDescriptionLabel->setStyleSheet(jobDescriptionStyle);

    QString const jobDescription = QString("<b>Текущая работа:</b><br>"
                                           "<b>Название:</b> %1<br>"
                                           "<b>Зарплата:</b> %2<br>"
                                           "<b>Расход энергии:</b> %3<br>"
                                           "<b>Упадок здоровья:</b> %4<br>"
                                           "<b>Упадок счастья:</b> %5")
                                       .arg(name)
                                       .arg(salary)
                                       .arg(energyDecrease)
                                       .arg(healthDecrease)
                                       .arg(happinessDecrease);

    jobDescriptionLabel->setText(jobDescription);
    jobDescriptionLabel->setVisible(true);
}

void JobsPage::applyLabelStyle(QLabel* label)
{
    label->setStyleSheet("QLabel {"
                         "    font-size: 20px;"
                         "    color: white;"
                         "    margin-bottom: 10px;"
                         "    qproperty-alignment: AlignTop;"
                         "}");
}

void JobsPage::applyButtonStyle(QPushButton* button)
{
    button->setStyleSheet("QPushButton {"
                          "    background-color: #3498DB;"
                          "    border: none;"
                          "    color: white;"
                          "    padding: 10px 20px;"
                          "    font-size: 16px;"
                          "    border-radius: 4px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #2980B9;"
                          "    color: white;"
                          "    border: 1px solid #3498DB;"
                          "}");

    button->setFixedWidth(200);
}

void JobsPage::applyJobApplyButtonStyle(QPushButton* button)
{
    button->setStyleSheet("QPushButton {"
                          "    background-color: #4CAF50;"
                          "    color: white;"
                          "    padding: 8px 16px;"
                          "    border: none;"
                          "    border-radius: 4px;"
                          "    text-align: center;"
                          "    text-decoration: none;"
                          "    font-size: 14px;"
                          "    margin: 4px 2px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #45a049;"
                          "    color: white;"
                          "    border: 1px solid #4CAF50;"
                          "}");
}

void JobsPage::applyTableStyle(QTableWidget* table)
{
    table->setStyleSheet("QTableWidget {"
                         "    background-color: white;"
                         "    border: 1px solid #3498DB;"
                         "    border-radius: 5px;"
                         "}"
                         "QTableWidget::item:selected {"
                         "    background-color: #3498DB;"
                         "    color: white;"
                         "}");

    table->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                             "    background-color: #3498DB;"
                                             "    color: white;"
                                             "    padding: 10px;"
                                             "    border: 1px solid #3498DB;"
                                             "}"
                                             "QHeaderView::section:checked {"
                                             "    background-color: #2980B9;"
                                             "}");

    table->verticalHeader()->setDefaultSectionSize(80);
}

