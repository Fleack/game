// characterpage.h
#ifndef CHARACTERPAGE_H
#define CHARACTERPAGE_H

#include <QLabel>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QWidget>

class CharacterPage : public QWidget
{
    Q_OBJECT

public:
    CharacterPage(const QString &playerName, QWidget *parent = nullptr);

    signals:
        void workClicked();
    void skillsClicked();
    void entertainmentClicked();
    void educationClicked();
    void backToMainMenuClicked();
    void nextYearClicked(); // Новый сигнал для кнопки "Следующий год"

private:
    QNetworkAccessManager *networkManager;
};

#endif // CHARACTERPAGE_H
