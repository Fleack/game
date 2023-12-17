// characterpage.cpp
#include "PlayerPage.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QVBoxLayout>

PlayerPage::PlayerPage(QWidget* parent)
    : QWidget(parent)
    , networkManager(new QNetworkAccessManager(this))
{
    // Buttons
    QVBoxLayout* layout = new QVBoxLayout(this);
    createPlayerStats(layout);
    createButtons(layout);
}

void PlayerPage::createPlayerStats(QVBoxLayout* layout)
{
    QLabel* nameLabel = new QLabel("Имя: ", this);
    QLabel* healthLabel = new QLabel("Здоровье: ", this);
    QLabel* energyLabel = new QLabel("Энергия: ", this);
    QLabel* happinessLabel = new QLabel("Счастье: ", this);
    QLabel* ageLabel = new QLabel("Возраст: ", this);
    QLabel* moneyLabel = new QLabel("Деньги: ", this);
    QLabel* jobLabel = new QLabel("Работа: ", this);

    layout->addWidget(nameLabel);
    layout->addWidget(healthLabel);
    layout->addWidget(energyLabel);
    layout->addWidget(happinessLabel);
    layout->addWidget(ageLabel);
    layout->addWidget(moneyLabel);
    layout->addWidget(jobLabel);

    // Делаем запрос к серверу для получения статистики игрока
    QJsonObject jsonObject;
    jsonObject["command"] = "get_player_stats";

    QNetworkRequest request(QUrl("http://localhost:12345")); // Замените на ваш URL сервера

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = networkManager->post(request, QJsonDocument(jsonObject).toJson());

    // Обработка ответа
    connect(reply, &QNetworkReply::finished, [this, reply, nameLabel, healthLabel, energyLabel, happinessLabel, ageLabel, moneyLabel, jobLabel]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

            if (jsonResponse.isObject())
            {
                QJsonObject playerStats = jsonResponse.object();

                nameLabel->setText("Имя: " + playerStats["name"].toString());
                healthLabel->setText("Здоровье: " + QString::number(playerStats["health"].toDouble()));
                energyLabel->setText("Энергия: " + QString::number(playerStats["energy"].toDouble()));
                happinessLabel->setText("Счастье: " + QString::number(playerStats["happiness"].toDouble()));
                ageLabel->setText("Возраст: " + QString::number(playerStats["age"].toInt()));
                moneyLabel->setText("Деньги: " + QString::number(playerStats["money"].toInt()));

                if (playerStats.contains("job") && playerStats["job"].isObject())
                {
                    QJsonObject jobInfo = playerStats["job"].toObject();
                    jobLabel->setText("Работа: " + jobInfo["name"].toString());
                }
                else
                {
                    jobLabel->setText("Работа: Нет");
                }
            }
        }
        else
        {
            // Ошибка при отправке запроса
            qDebug() << "Error: " << reply->errorString();
        }

        reply->deleteLater();
    });
}

void PlayerPage::createButtons(QVBoxLayout* layout)
{
    QPushButton* jobsButton = new QPushButton("Работа", this);
    QPushButton* skillsButton = new QPushButton("Умения", this);
    QPushButton* entertainmentButton = new QPushButton("Развлечения", this);
    QPushButton* educationButton = new QPushButton("Обучение", this);
    QPushButton* backButton = new QPushButton("Назад", this);

    layout->addWidget(jobsButton);
    layout->addWidget(skillsButton);
    layout->addWidget(entertainmentButton);
    layout->addWidget(educationButton);
    layout->addWidget(backButton);

    connect(jobsButton, &QPushButton::clicked, this, &PlayerPage::jobsClicked);
    connect(skillsButton, &QPushButton::clicked, this, &PlayerPage::skillsClicked);
    connect(entertainmentButton, &QPushButton::clicked, this, &PlayerPage::entertainmentClicked);
    connect(educationButton, &QPushButton::clicked, this, &PlayerPage::educationClicked);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        // Добавим подтверждающий диалог
        QMessageBox msgBox(
            QMessageBox::Question,
            "Вернуться в главное меню",
            "Вы уверены, что хотите вернуться в главное меню?",
            QMessageBox::Yes | QMessageBox::No,
            this);
        msgBox.setDefaultButton(QMessageBox::No);

        int ret = msgBox.exec();
        if (ret == QMessageBox::Yes)
        {
            emit backToMainMenuClicked();
        }
    });
}

