#pragma once

#include <QLabel>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QWidget>

class EntertainmentPage final : public QWidget
{
    Q_OBJECT

public:
    explicit EntertainmentPage(QWidget* parent = nullptr);

signals:
    void backToPlayerPageClicked();

private slots:
    void onEntertainClicked();
    void onBackClicked();

private:
    void createLayout();
    void applyButtonStyle(QPushButton* button);
    void applyDescriptionLabelStyle(QLabel* label);

private:
    QNetworkAccessManager* m_networkManager;
};
