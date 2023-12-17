// createplayerpage.h
#ifndef CREATEPLAYERPAGE_H
#define CREATEPLAYERPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class CreatePlayerPage : public QWidget
{
    Q_OBJECT

public:
    CreatePlayerPage(QWidget *parent = nullptr);

    signals:
        void backClicked();
    void createPlayerClicked(const QString &playerName);

    private slots:
        void onCreateClicked();

private:
    QNetworkAccessManager *networkManager;
};

#endif // CREATEPLAYERPAGE_H
