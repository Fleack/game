// playerpage.hpp
#ifndef PLAYERPAGE_H
#define PLAYERPAGE_H

#include "EntertainmentPage.hpp"

#include <QLabel>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class PlayerPage : public QWidget
{
    Q_OBJECT

public:
    PlayerPage(QWidget* parent = nullptr);

signals:
    void jobsClicked();
    void skillsClicked();
    void entertainmentClicked();
    void educationClicked();
    void backToMainMenuClicked();

private:
    void createPlayerStats(QVBoxLayout*);
    void createButtons(QVBoxLayout*);
    void nextYearClicked();

private:
    QNetworkAccessManager* networkManager;
};

#endif // PLAYERPAGE_H
