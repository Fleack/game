#include "MainWindow.hpp"

#include <QApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QPainter>
#include <QtGlobal>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
    setupUI();

    connect(m_startGameButton, &QPushButton::clicked, this, &MainWindow::onStartGameClicked);
    connect(m_exitButton, &QPushButton::clicked, this, &MainWindow::onExitClicked);
    // connect(this, &MainWindow::destroyed, this, &MainWindow::onExitClicked); TODO Fix game close by cross

    resize(800, 450);
}

MainWindow::~MainWindow()
{
    delete m_networkManager;
    delete m_startGameButton;
    delete m_exitButton;
    delete m_mainLayout;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(135, 206, 250));
}

void MainWindow::setupUI()
{
    m_startGameButton = new QPushButton("Начать игру", this);
    m_startGameButton->setObjectName("StartGameButton");

    m_exitButton = new QPushButton("Выйти", this);
    m_exitButton->setObjectName("ExitButton");

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->addWidget(m_startGameButton);
    m_mainLayout->addWidget(m_exitButton);
    m_mainLayout->setAlignment(Qt::AlignCenter);

    auto const centralWidget = new QWidget(this);
    centralWidget->setLayout(m_mainLayout);
    setCentralWidget(centralWidget);

    m_startGameButton->setStyleSheet("QPushButton#StartGameButton {"
                                     "   background-color: #3498db;"
                                     "   border: 2px solid #2980b9;"
                                     "   color: white;"
                                     "   padding: 10px 20px;"
                                     "   font-size: 18px;"
                                     "}"
                                     "QPushButton#StartGameButton:hover {"
                                     "   background-color: #2980b9;"
                                     "}");

    m_exitButton->setStyleSheet("QPushButton#ExitButton {"
                                "   background-color: #e74c3c;"
                                "   border: 2px solid #c0392b;"
                                "   color: white;"
                                "   padding: 10px 20px;"
                                "   font-size: 18px;"
                                "}"
                                "QPushButton#ExitButton:hover {"
                                "   background-color: #c0392b;"
                                "}");
}

void MainWindow::onStartGameClicked()
{
    // Ваш код для начала игры
}

void MainWindow::onExitClicked()
{
    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["command"] = "terminate_session";

    QJsonDocument const doc(json);
    QByteArray const data = doc.toJson();

    QNetworkReply const* reply = m_networkManager->post(request, data);

    connect(reply, &QNetworkReply::finished, [this]() {
#ifdef DEBUG
        qDebug() << "Request sent successfully";
#endif
        qApp->quit();
    });
}
