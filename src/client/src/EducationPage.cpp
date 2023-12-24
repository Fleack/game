#include "EducationPage.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QNetworkReply>
#include <QPushButton>
#include <QVBoxLayout>

EducationPage::EducationPage(QWidget* parent)
    : QWidget(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
    createLayout();
}

void EducationPage::createLayout()
{
    auto* layout = new QVBoxLayout(this);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("EducationPage {"
                  "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #2C3E50, stop:1 #34495E);"
                  "}");

    auto* descriptionLabel = new QLabel("Больше активностей будет добавлено в будущем...\n\n"
                                        "Характеристики:\n"
                                        "Энергия: -10\n"
                                        "Счастье: -10\n"
                                        "Деньги: -10000\n"
                                        "Навыки: +10 ко всем", this);

    descriptionLabel->setObjectName("descriptionLabel");

    applyDescriptionLabelStyle(descriptionLabel);

    auto* buyAndLearnButton = new QPushButton("Купить и изучить", this);
    auto* backButton = new QPushButton("Назад", this);

    buyAndLearnButton->setObjectName("buyAndLearnButton");
    backButton->setObjectName("backButton");

    applyButtonStyle(buyAndLearnButton);
    applyButtonStyle(backButton);

    layout->addWidget(descriptionLabel, 0, Qt::AlignHCenter);
    layout->addWidget(buyAndLearnButton, 0, Qt::AlignHCenter);
    layout->addWidget(backButton, 0, Qt::AlignHCenter);

    connect(buyAndLearnButton, &QPushButton::clicked, this, &EducationPage::onBuyAndLearnClicked);
    connect(backButton, &QPushButton::clicked, this, &EducationPage::onBackClicked);
}

void EducationPage::onBuyAndLearnClicked()
{
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "perform_education_activity";

    QJsonDocument const requestData(requestBody);
    QByteArray const requestDataBytes = requestData.toJson();

    QNetworkReply* reply = m_networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [reply]() {
        reply->deleteLater();
    });
}

void EducationPage::onBackClicked()
{
    emit backToPlayerPageClicked();
}

void EducationPage::applyButtonStyle(QPushButton* button)
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

void EducationPage::applyDescriptionLabelStyle(QLabel* label)
{
    label->setStyleSheet("QLabel {"
                         "    color: white;"
                         "    padding: 15px;"
                         "    font-size: 18px;"
                         "    font-weight: bold;"
                         "}");
}
