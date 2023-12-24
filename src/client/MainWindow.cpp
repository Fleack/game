#include "MainWindow.hpp"

#include "EducationPage.hpp"
#include "EntertainmentPage.hpp"
#include "JobsPage.hpp"
#include "MainMenuPage.hpp"
#include "PlayerSkillsPage.hpp"

#include <QCloseEvent>
#include <qeventloop.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
{
    auto* mainMenuPage = new MainMenuPage(this);

    connect(mainMenuPage, &MainMenuPage::newGameClicked, this, &MainWindow::onNewGameClicked);
    connect(mainMenuPage, &MainMenuPage::exitClicked, this, &MainWindow::onExitClicked);

    setCentralWidget(mainMenuPage);

    setFixedSize(800, 890);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
    timer->start(30000);
}

void MainWindow::onNewGameClicked()
{
    auto* createPlayerPage = new CreatePlayerPage(this);

    connect(createPlayerPage, &CreatePlayerPage::backClicked, this, &MainWindow::onBackToMainMenuClicked);
    connect(createPlayerPage, &CreatePlayerPage::createPlayerClicked, this, &MainWindow::onCreatePlayerClicked);

    setCentralWidget(createPlayerPage);
}

void MainWindow::onBackToMainMenuClicked()
{
    auto* mainMenuPage = new MainMenuPage(this);

    connect(mainMenuPage, &MainMenuPage::newGameClicked, this, &MainWindow::onNewGameClicked);
    connect(mainMenuPage, &MainMenuPage::exitClicked, this, &MainWindow::onExitClicked);

    setCentralWidget(mainMenuPage);
}

void MainWindow::onCreatePlayerClicked()
{
    auto* playerPage = new PlayerPage(this);

    connect(playerPage, &PlayerPage::backToMainMenuClicked, this, &MainWindow::onBackToMainMenuClicked);
    connect(playerPage, &PlayerPage::skillsClicked, this, &MainWindow::onSkillsClicked);
    connect(playerPage, &PlayerPage::jobsClicked, this, &MainWindow::onJobsClicked);
    connect(playerPage, &PlayerPage::entertainmentClicked, this, &MainWindow::onEntertainmentClicked);
    connect(playerPage, &PlayerPage::educationClicked, this, &MainWindow::onEducationClicked);

    setCentralWidget(playerPage);
}

void MainWindow::onEntertainmentClicked()
{
    auto* entertainmentPage = new EntertainmentPage(this);

    connect(entertainmentPage, &EntertainmentPage::backToPlayerPageClicked, this, &MainWindow::onCreatePlayerClicked);

    setCentralWidget(entertainmentPage);
}

void MainWindow::onEducationClicked()
{
    auto* educationPage = new EducationPage(this);

    connect(educationPage, &EducationPage::backToPlayerPageClicked, this, &MainWindow::onCreatePlayerClicked);

    setCentralWidget(educationPage);
}

void MainWindow::onSkillsClicked()
{
    auto* skillsPage = new PlayerSkillsPage(this);

    connect(skillsPage, &PlayerSkillsPage::backToPlayerPageClicked, this, &MainWindow::onCreatePlayerClicked);

    setCentralWidget(skillsPage);
}

void MainWindow::onJobsClicked()
{
    auto* jobsPage = new JobsPage(this);

    connect(jobsPage, &JobsPage::backToPlayerPageClicked, this, &MainWindow::onCreatePlayerClicked);

    setCentralWidget(jobsPage);
}

void MainWindow::onExitClicked()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Выход", "Вы уверены, что хотите выйти?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        terminateServer();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::onTimerTimeout()
{
    QNetworkAccessManager networkManager;
    QJsonObject jsonObject;
    jsonObject["command"] = "timer";

    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = networkManager.post(request, QJsonDocument(jsonObject).toJson());

    qDebug() << "Timer request sent";

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        qDebug() << "Timer request finished successfully. Response: " << responseData;
    }
    else
    {
        qDebug() << "Timer request failed. Error: " << reply->errorString();
    }

    reply->deleteLater();
}

void MainWindow::terminateServer()
{
    QNetworkAccessManager networkManager;
    QJsonObject jsonObject;
    jsonObject["command"] = "terminate_session";

    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = networkManager.post(request, QJsonDocument(jsonObject).toJson());

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    reply->deleteLater();
}
