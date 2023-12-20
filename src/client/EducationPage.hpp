#pragma once

#include <QLabel>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QWidget>

class EducationPage final : public QWidget
{
    Q_OBJECT

public:
    explicit EducationPage(QWidget* parent = nullptr);

signals:
    void backToPlayerPageClicked();

private slots:
    void onBuyAndLearnClicked();
    void onBackClicked();

private:
    void createLayout();
    void applyDescriptionLabelStyle(QLabel* label);
    void applyButtonStyle(QPushButton* button);

private:
    QNetworkAccessManager* m_networkManager;
};
