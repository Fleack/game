// educationpage.cpp
#include "EducationPage.hpp"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QNetworkReply>
#include <QNetworkRequest>

class QNetworkReply;
EducationPage::EducationPage(QWidget* parent)
    : QWidget(parent)
    , networkManager(new QNetworkAccessManager(this))
{
    createLayout();
}

void EducationPage::createLayout()
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* descriptionLabel = new QLabel("Больше активностей будет добавлено в будущем...\n\nХарактеристика:\nЭнергия -10\nСчастье -10\nДеньги -10000\nНавыки: +10 ко всем", this);
    layout->addWidget(descriptionLabel);

    QPushButton* buyAndLearnButton = new QPushButton("Купить и изучить", this);
    layout->addWidget(buyAndLearnButton);

    connect(buyAndLearnButton, &QPushButton::clicked, this, &EducationPage::onBuyAndLearnClicked);

    QPushButton* backButton = new QPushButton("Назад", this);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &EducationPage::onBackClicked);
}

void EducationPage::onBuyAndLearnClicked()
{
    // Send a request to the server with command = "perform_education_activity"
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "perform_education_activity";

    QJsonDocument requestData(requestBody);
    QByteArray requestDataBytes = requestData.toJson();

    QNetworkReply* reply = networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            qDebug() << "Successfully performed education activity";
        }
        else
        {
            qDebug() << "Error performing education activity:" << reply->errorString();
        }

        reply->deleteLater();
    });
}

void EducationPage::onBackClicked()
{
    emit backToPlayerPageClicked();
}
