#include "CreatePlayerPage.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>

CreatePlayerPage::CreatePlayerPage(QWidget* parent)
    : QWidget(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
    auto* layout = new QVBoxLayout(this);

    auto* nameLineEdit = new QLineEdit(this);
    auto* createButton = new QPushButton("Создать", this);
    auto* backButton = new QPushButton("Назад", this);

    createButton->setObjectName("Создать");
    backButton->setObjectName("Назад");

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("CreatePlayerPage {"
                  "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #2C3E50, stop:1 #34495E);"
                  "}");

    nameLineEdit->setStyleSheet("QLineEdit {"
                               "    background-color: #ECF0F1;"
                               "    border: 1px solid #BDC3C7;"
                               "    padding: 8px;"
                               "    border-radius: 4px;"
                               "}");

    nameLineEdit->setPlaceholderText("Введите имя");

    applyButtonStyle(createButton);
    applyButtonStyle(backButton);

    createButton->setFixedWidth(200);
    backButton->setFixedWidth(200);

    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layout->addWidget(nameLineEdit, 0, Qt::AlignHCenter);
    layout->addWidget(createButton, 0, Qt::AlignHCenter);
    layout->addWidget(backButton, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    connect(backButton, &QPushButton::clicked, this, &CreatePlayerPage::backClicked);
    connect(createButton, &QPushButton::clicked, this, &CreatePlayerPage::onCreateClicked);
}

void CreatePlayerPage::onCreateClicked()
{
    auto* nameLineEdit = findChild<QLineEdit*>();
    if (!nameLineEdit)
    {
        qDebug() << "nameLineEdit is nullptr!";
        return;
    }

    QString const playerName = nameLineEdit->text();

    if (playerName.isEmpty())
    {
        nameLineEdit->setStyleSheet("QLineEdit { border: 1px solid red; }");
        return;
    }

    nameLineEdit->setStyleSheet("");

    QJsonObject jsonObject;
    jsonObject["command"] = "create_player";
    jsonObject["player_name"] = playerName;

    QNetworkRequest request(QUrl("http://localhost:12345"));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_networkManager->post(request, QJsonDocument(jsonObject).toJson());

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) { emit createPlayerClicked(); }

        reply->deleteLater();
    });
}

void CreatePlayerPage::applyButtonStyle(QPushButton* button)
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
