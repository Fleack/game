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
    PlayerPage(QString const& playerName, QWidget* parent = nullptr);

signals:
    void workClicked();
    void skillsClicked();
    void entertainmentClicked();
    void educationClicked();
    void backToMainMenuClicked();
    void nextYearClicked(); // Новый сигнал для кнопки "Следующий год"

private:
    void createPlayerStats(QVBoxLayout*, QString const& playerName);
    void createButtons(QVBoxLayout*);

private:
    QNetworkAccessManager* networkManager;
};

#endif // CHARACTERPAGE_H
