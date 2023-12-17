// playerskillspage.cpp
#include "PlayerSkillsPage.hpp"

#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

PlayerSkillsPage::PlayerSkillsPage(QWidget* parent)
    : QWidget(parent)
    , networkManager(new QNetworkAccessManager(this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QTableWidget* skillsTable = new QTableWidget(this);
    skillsTable->setObjectName("skillsTable");
    skillsTable->setColumnCount(2);
    skillsTable->setHorizontalHeaderLabels({"Умение", "Значение"});
    skillsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPushButton* backButton = new QPushButton("Назад", this);

    layout->addWidget(skillsTable);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &PlayerSkillsPage::onBackClicked);
    connect(this, &PlayerSkillsPage::backToMainMenuClicked, this, &PlayerSkillsPage::onBackClicked);

    fetchPlayerSkills();
}

void PlayerSkillsPage::onBackClicked()
{
    emit backToMainMenuClicked();
}

void PlayerSkillsPage::fetchPlayerSkills()
{
    QJsonObject jsonObject;
    jsonObject["command"] = "get_player_skills";

    QNetworkRequest request(QUrl("http://localhost:12345")); // Замените на ваш URL сервера

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = networkManager->post(request, QJsonDocument(jsonObject).toJson());

    // Обработка ответа
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

            if (jsonResponse.isArray())
            {
                QJsonArray skillsArray = jsonResponse.array();

                QTableWidget* skillsTable = findChild<QTableWidget*>("skillsTable");
                if (skillsTable)
                {
                    skillsTable->setRowCount(skillsArray.size());

                    for (int i = 0; i < skillsArray.size(); ++i)
                    {
                        QJsonObject skillObject = skillsArray[i].toObject();
                        QString skillName = skillObject["name"].toString();
                        int skillValue = skillObject["value"].toInt();

                        QTableWidgetItem* nameItem = new QTableWidgetItem(skillName);
                        QTableWidgetItem* valueItem = new QTableWidgetItem(QString::number(skillValue));

                        skillsTable->setItem(i, 0, nameItem);
                        skillsTable->setItem(i, 1, valueItem);
                    }
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
