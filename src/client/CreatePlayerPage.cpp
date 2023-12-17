// createplayerpage.cpp
#include "CreatePlayerPage.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QVBoxLayout>

CreatePlayerPage::CreatePlayerPage(QWidget* parent)
    : QWidget(parent)
    , networkManager(new QNetworkAccessManager(this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLineEdit* nameLineEdit = new QLineEdit(this);
    nameLineEdit->setPlaceholderText("Введите имя");
    QPushButton* createButton = new QPushButton("Создать", this);
    QPushButton* backButton = new QPushButton("Назад", this);

    layout->addWidget(nameLineEdit);
    layout->addWidget(createButton);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &CreatePlayerPage::backClicked);
    connect(createButton, &QPushButton::clicked, this, &CreatePlayerPage::onCreateClicked);
}

void CreatePlayerPage::onCreateClicked()
{
    QLineEdit* nameLineEdit = dynamic_cast<QLineEdit*>(layout()->itemAt(0)->widget());
    if (!nameLineEdit)
    {
        qDebug() << "nameLineEdit is nullptr!";
        return;
    }

    QString playerName = nameLineEdit->text();

    if (playerName.isEmpty())
    {
        // Если имя пустое, устанавливаем стиль с красной рамкой
        nameLineEdit->setStyleSheet("border: 1px solid red;");
        return;
    }

    // Сбросите стиль, если поле валидно
    nameLineEdit->setStyleSheet("");

    QJsonObject jsonObject;
    jsonObject["command"] = "create_player";
    jsonObject["player_name"] = playerName;

    QNetworkRequest request(QUrl("http://localhost:12345")); // Замените на ваш URL сервера

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = networkManager->post(request, QJsonDocument(jsonObject).toJson());

    // Обработка ответа
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            // Успешный ответ от сервера, можно добавить дополнительную логику
            emit createPlayerClicked();
        }
        else
        {
            // Ошибка при отправке запроса
            qDebug() << "Error: " << reply->errorString();
        }

        reply->deleteLater();
    });
}
