// entertainmentpage.cpp
#include "EntertainmentPage.hpp"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QNetworkReply>

EntertainmentPage::EntertainmentPage(QWidget* parent)
    : QWidget(parent)
    , networkManager(new QNetworkAccessManager(this))
{
    createLayout();
}

void EntertainmentPage::createLayout()
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* descriptionLabel = new QLabel("Больше активностей будет добавлено в будущем...\n\nХарактеристика:\nЭнергия +5\nЗдоровье +5\nСчастье +15\nДеньги -500", this);
    layout->addWidget(descriptionLabel);

    QPushButton* entertainButton = new QPushButton("Пойти развлечься", this);
    layout->addWidget(entertainButton);

    connect(entertainButton, &QPushButton::clicked, this, &EntertainmentPage::onEntertainClicked);

    QPushButton* backButton = new QPushButton("Назад", this);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &EntertainmentPage::onBackClicked);
}

void EntertainmentPage::onEntertainClicked()
{
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject requestBody;
    requestBody["command"] = "perform_entertainment_activity";

    QJsonDocument requestData(requestBody);
    QByteArray requestDataBytes = requestData.toJson();

    QNetworkReply* reply = networkManager->post(request, requestDataBytes);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            qDebug() << "Successfully performed entertainment activity";

            // Optionally, update the UI or take other actions if needed
        }
        else
        {
            qDebug() << "Error performing entertainment activity:" << reply->errorString();
        }

        reply->deleteLater();
    });
}

void EntertainmentPage::onBackClicked()
{
    // Emit the signal when the "Назад" button is clicked
    emit backToPlayerPageClicked();
}
