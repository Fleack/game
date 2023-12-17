// createplayerpage.h
#ifndef CREATEPLAYERPAGE_H
#define CREATEPLAYERPAGE_H

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
#include <QWidget>

class CreatePlayerPage : public QWidget
{
    Q_OBJECT

public:
    CreatePlayerPage(QWidget* parent = nullptr);

signals:
    void backClicked();
    void createPlayerClicked();

private slots:
    void onCreateClicked();

private:
    QNetworkAccessManager* networkManager;
};

#endif // CREATEPLAYERPAGE_H
