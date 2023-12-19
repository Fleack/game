#pragma once

#include <QLineEdit>
#include <QNetworkReply>
#include <QPushButton>
#include <QWidget>

class CreatePlayerPage final : public QWidget
{
    Q_OBJECT

public:
    explicit CreatePlayerPage(QWidget* parent = nullptr);

signals:
    void backClicked();
    void createPlayerClicked();

private slots:
    void onCreateClicked();

private:
    void applyStyles(QWidget* widget);
    void applyButtonStyle(QPushButton* button);

private:
    QNetworkAccessManager* m_networkManager;
};
