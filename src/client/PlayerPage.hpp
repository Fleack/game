// characterpage.h
#ifndef CHARACTERPAGE_H
#define CHARACTERPAGE_H

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
    void nextYearClicked();

private:
    void createPlayerStats(QVBoxLayout*);
    void createButtons(QVBoxLayout*);

private:
    QNetworkAccessManager* networkManager;
};

#endif // CHARACTERPAGE_H
