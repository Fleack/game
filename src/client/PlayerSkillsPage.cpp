#include "PlayerSkillsPage.hpp"

#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QVBoxLayout>

PlayerSkillsPage::PlayerSkillsPage(QWidget* parent)
    : QWidget(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
    auto* layout = new QVBoxLayout(this);
    auto* skillsTable = new QTableWidget(this);
    auto* backButton = new QPushButton("Назад", this);

    backButton->setObjectName("backButton");
    skillsTable->setObjectName("skillsTable");

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("PlayerSkillsPage {"
                  "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #2C3E50, stop:1 #34495E);"
                  "}");

    skillsTable->setObjectName("skillsTable");
    skillsTable->setColumnCount(2);
    skillsTable->setHorizontalHeaderLabels({"Умение", "Значение"});
    skillsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(skillsTable);

    applyButtonStyle(backButton);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &PlayerSkillsPage::onBackClicked);

    fetchPlayerSkills();
}

void PlayerSkillsPage::onBackClicked()
{
    emit backToPlayerPageClicked();
}

void PlayerSkillsPage::fetchPlayerSkills()
{
    QJsonObject jsonObject;
    jsonObject["command"] = "get_player_skills";

    QNetworkRequest request(QUrl("http://localhost:12345"));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_networkManager->post(request, QJsonDocument(jsonObject).toJson());

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray const responseData = reply->readAll();
            QJsonDocument const jsonResponse = QJsonDocument::fromJson(responseData);

            if (jsonResponse.isArray())
            {
                QJsonArray skillsArray = jsonResponse.array();

                auto* skillsTable = findChild<QTableWidget*>("skillsTable");
                if (skillsTable)
                {
                    skillsTable->setRowCount(skillsArray.size());

                    for (int i = 0; i < skillsArray.size(); ++i)
                    {
                        QJsonObject skillObject = skillsArray[i].toObject();
                        QString skillName = skillObject["name"].toString();
                        const int skillValue = skillObject["value"].toInt();

                        auto* nameItem = new QTableWidgetItem(skillName);
                        auto* valueItem = new QTableWidgetItem(QString::number(skillValue));

                        skillsTable->setItem(i, 0, nameItem);
                        skillsTable->setItem(i, 1, valueItem);
                    }
                }
            }

            auto* skillsTable = findChild<QTableWidget*>("skillsTable");
            if (skillsTable) { applyTableStyle(skillsTable); }
        }

        reply->deleteLater();
    });
}

void PlayerSkillsPage::applyTableStyle(QTableWidget* table)
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

void PlayerSkillsPage::applyButtonStyle(QPushButton* button)
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
