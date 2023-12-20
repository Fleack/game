#include "EntertainmentPage.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QNetworkReply>
#include <QPushButton>
#include <QVBoxLayout>

EntertainmentPage::EntertainmentPage(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("EntertainmentPage {"
                  "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #2C3E50, stop:1 #34495E);"
                  "}");

    auto* descriptionLabel = new QLabel("Больше активностей будет добавлено в будущем...\n\n"
                                        "Характеристики:\n"
                                        "Энергия: -5\n"
                                        "Здоровье: +5\n"
                                        "Счастье: +15\n"
                                        "Деньги: -500", this);
    applyDescriptionLabelStyle(descriptionLabel);

    auto* entertainButton = new QPushButton("Пойти развлечься", this);
    auto* backButton = new QPushButton("Назад", this);

    applyButtonStyle(entertainButton);
    applyButtonStyle(backButton);

    layout->addWidget(descriptionLabel, 0, Qt::AlignHCenter);
    layout->addWidget(entertainButton, 0, Qt::AlignHCenter);
    layout->addWidget(backButton, 0, Qt::AlignHCenter);

    connect(entertainButton, &QPushButton::clicked, this, &EntertainmentPage::onEntertainClicked);
    connect(backButton, &QPushButton::clicked, this, &EntertainmentPage::onBackClicked);
}

void EntertainmentPage::onEntertainClicked()
{
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "perform_entertainment_activity";

    QJsonDocument const requestData(requestBody);
    QByteArray const requestDataBytes = requestData.toJson();

    QNetworkReply* reply = m_networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [reply]() {
        reply->deleteLater();
    });
}

void EntertainmentPage::onBackClicked()
{
    emit backToPlayerPageClicked();
}

void EntertainmentPage::applyButtonStyle(QPushButton* button)
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

void EntertainmentPage::applyDescriptionLabelStyle(QLabel* label)
{
    label->setStyleSheet("QLabel {"
                         "    color: white;"
                         "    padding: 15px;"
                         "    font-size: 18px;"
                         "    font-weight: bold;"
                         "}");
}
