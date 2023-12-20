#include "PlayerPage.hpp"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPushButton>
#include <QVBoxLayout>

PlayerPage::PlayerPage(QWidget* parent)
    : QWidget(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
    auto* layout = new QVBoxLayout(this);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("PlayerPage {"
                  "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #2C3E50, stop:1 #34495E);"
                  "}");

    createPlayerStats(layout);

    createButtons(layout);
}

void PlayerPage::createPlayerStats(QVBoxLayout* layout)
{
    clearPage(layout);

    auto* nameLabel = new QLabel(this);
    auto* healthLabel = new QLabel(this);
    auto* energyLabel = new QLabel(this);
    auto* happinessLabel = new QLabel(this);
    auto* ageLabel = new QLabel(this);
    auto* moneyLabel = new QLabel(this);
    auto* jobLabel = new QLabel(this);

    applyLabelStyle(nameLabel);
    applyLabelStyle(healthLabel);
    applyLabelStyle(energyLabel);
    applyLabelStyle(happinessLabel);
    applyLabelStyle(ageLabel);
    applyLabelStyle(moneyLabel);
    applyLabelStyle(jobLabel);

    layout->addWidget(nameLabel, 0, Qt::AlignHCenter);
    layout->addWidget(healthLabel, 0, Qt::AlignHCenter);
    layout->addWidget(energyLabel, 0, Qt::AlignHCenter);
    layout->addWidget(happinessLabel, 0, Qt::AlignHCenter);
    layout->addWidget(ageLabel, 0, Qt::AlignHCenter);
    layout->addWidget(moneyLabel, 0, Qt::AlignHCenter);
    layout->addWidget(jobLabel, 0, Qt::AlignHCenter);

    QJsonObject jsonObject;
    jsonObject["command"] = "get_player_stats";

    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_networkManager->post(request, QJsonDocument(jsonObject).toJson());

    connect(reply, &QNetworkReply::finished, [this, reply, nameLabel, healthLabel, energyLabel, happinessLabel, ageLabel, moneyLabel, jobLabel]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray const responseData = reply->readAll();
            QJsonDocument const jsonResponse = QJsonDocument::fromJson(responseData);

            if (jsonResponse.isObject())
            {
                QJsonObject playerStats = jsonResponse.object();

                updateLabelWithColor(nameLabel, "<b>Имя:</b> " + playerStats["name"].toString(), Qt::white);
                updateLabelWithColor(healthLabel, "<b>Здоровье:</b> " + QString::number(playerStats["health"].toDouble()), getColorForValue(playerStats["health"].toDouble()));
                updateLabelWithColor(energyLabel, "<b>Энергия:</b> " + QString::number(playerStats["energy"].toDouble()), getColorForValue(playerStats["energy"].toDouble()));
                updateLabelWithColor(happinessLabel, "<b>Счастье:</b> " + QString::number(playerStats["happiness"].toDouble()), getColorForValue(playerStats["happiness"].toDouble()));
                updateLabelWithColor(ageLabel, "<b>Возраст:</b> " + QString::number(playerStats["age"].toInt()), Qt::white);
                updateLabelWithColor(moneyLabel, "<b>Деньги:</b> " + QString::number(playerStats["money"].toInt()), Qt::white);

                if (playerStats.contains("job") && playerStats["job"].isObject())
                {
                    QJsonObject jobInfo = playerStats["job"].toObject();
                    updateLabelWithColor(jobLabel, "<b>Работа:</b> " + jobInfo["name"].toString(), Qt::white);
                }
                else
                {
                    updateLabelWithColor(jobLabel, "<b>Работа:</b> Нет", Qt::white);
                }
            }
        }

        reply->deleteLater();
    });
}

void PlayerPage::createButtons(QVBoxLayout* layout)
{
    auto* jobsButton = new QPushButton("Работа", this);
    auto* skillsButton = new QPushButton("Умения", this);
    auto* entertainmentButton = new QPushButton("Развлечения", this);
    auto* educationButton = new QPushButton("Обучение", this);
    auto* backButton = new QPushButton("Назад", this);
    auto* nextYearButton = new QPushButton("Следующий год", this);

    applyButtonStyle(nextYearButton);
    applyButtonStyle(jobsButton);
    applyButtonStyle(skillsButton);
    applyButtonStyle(entertainmentButton);
    applyButtonStyle(educationButton);
    applyButtonStyle(backButton);

    nextYearButton->setFixedWidth(200);
    jobsButton->setFixedWidth(200);
    skillsButton->setFixedWidth(200);
    entertainmentButton->setFixedWidth(200);
    educationButton->setFixedWidth(200);
    backButton->setFixedWidth(200);

    layout->addWidget(nextYearButton, 0, Qt::AlignHCenter);
    layout->addWidget(jobsButton, 0, Qt::AlignHCenter);
    layout->addWidget(skillsButton, 0, Qt::AlignHCenter);
    layout->addWidget(entertainmentButton, 0, Qt::AlignHCenter);
    layout->addWidget(educationButton, 0, Qt::AlignHCenter);
    layout->addWidget(backButton, 0, Qt::AlignHCenter);

    connect(nextYearButton, &QPushButton::clicked, this, &PlayerPage::nextYearClicked);
    connect(jobsButton, &QPushButton::clicked, this, &PlayerPage::jobsClicked);
    connect(skillsButton, &QPushButton::clicked, this, &PlayerPage::skillsClicked);
    connect(entertainmentButton, &QPushButton::clicked, this, &PlayerPage::entertainmentClicked);
    connect(educationButton, &QPushButton::clicked, this, &PlayerPage::educationClicked);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        QMessageBox msgBox(
            QMessageBox::Question,
            "Вернуться в главное меню",
            "Вы уверены, что хотите вернуться в главное меню?",
            QMessageBox::Yes | QMessageBox::No, this);
        msgBox.setDefaultButton(QMessageBox::No);

        if (msgBox.exec() == QMessageBox::Yes) { emit backToMainMenuClicked(); }
    });
}

void PlayerPage::nextYearClicked()
{
    QJsonObject jsonObject;
    jsonObject["command"] = "pass_year";

    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_networkManager->post(request, QJsonDocument(jsonObject).toJson());

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            auto* boxLayout = static_cast<QVBoxLayout*>(layout());
            createPlayerStats(boxLayout);
            createButtons(boxLayout);
        }

        reply->deleteLater();
    });
}

void PlayerPage::clearPage(QVBoxLayout* layout)
{
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr)
    {
        delete item->widget();
        delete item;
    }
}

void PlayerPage::applyLabelStyle(QLabel* label)
{
    label->setStyleSheet("QLabel {"
                         "    font-size: 20px;"
                         "    color: white;"
                         "    margin-bottom: 10px;"
                         "    qproperty-alignment: AlignTop;"
                         "}");
}

void PlayerPage::applyButtonStyle(QPushButton* button)
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

void PlayerPage::updateLabelWithColor(QLabel* label, const QString& text, const QColor& color)
{
    label->setText(text);
    label->setStyleSheet(QString("QLabel { font-size: 20px; color: %1; margin-bottom: 10px; qproperty-alignment: AlignTop; }").arg(color.name()));
}

QColor PlayerPage::getColorForValue(double value)
{
    if (value >= 70) {return QColor("#2ECC71");}
     if (value >= 40) {return QColor("#F1C40F");}
     return QColor("#E74C3C");
}
