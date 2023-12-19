// mainwindow.cpp
#include "MainWindow.hpp"

#include "EducationPage.hpp"
#include "JobsPage.hpp"

#include <QCloseEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}
{
    auto* mainMenuPage = new MainMenuPage(this);

    connect(mainMenuPage, &MainMenuPage::newGameClicked, this, &MainWindow::onNewGameClicked);
    connect(mainMenuPage, &MainMenuPage::exitClicked, this, &MainWindow::onExitClicked);

    setCentralWidget(mainMenuPage);
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
    // Handle the close event
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Выход", "Вы уверены, что хотите выйти?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        terminateServer();
        event->ignore();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::terminateServer()
{
    QNetworkAccessManager networkManager;
    QJsonObject jsonObject;
    jsonObject["command"] = "terminate_session";

    QNetworkRequest request(QUrl("http://localhost:12345"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = networkManager.post(request, QJsonDocument(jsonObject).toJson());

    qDebug() << "Terminate session request sent:\n" << jsonObject << '\n';

    connect(reply, &QNetworkReply::finished, [reply]() {
        reply->deleteLater();
    });
}
