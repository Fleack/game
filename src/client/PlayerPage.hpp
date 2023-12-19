#pragma once

#include <QLabel>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class PlayerPage final : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerPage(QWidget* parent = nullptr);

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
    void applyLabelStyle(QLabel* label);
    void applyButtonStyle(QPushButton* button);
    void updateLabelWithColor(QLabel* label, QString const& text, QColor const& color);
    QColor getColorForValue(double value);

    static void clearPage(QVBoxLayout*);

private:
    QNetworkAccessManager* m_networkManager;
};
