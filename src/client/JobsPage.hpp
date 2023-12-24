#pragma once

#include <QLabel>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>

class JobsPage final : public QWidget
{
    Q_OBJECT

public:
    explicit JobsPage(QWidget* parent = nullptr);

    void processJobs(QJsonDocument const& jsonDocument);
signals:
    void backToPlayerPageClicked();

private slots:
    void onBackClicked();
    void onApplyJobClicked(int jobId);
    void onQuitJobClicked();

private:
    void fetchJobs();
    void fetchPlayerJob();
    void processPlayerJob(QJsonDocument const& jsonDocument);
    void hideQuitJobButton(bool) const;
    void showVacanciesTable();
    void onWorkClicked();
    void createJobDescription(QJsonObject const& json, QLabel* jobDescriptionLabel);
    void applyLabelStyle(QLabel* label);
    void applyButtonStyle(QPushButton* button);
    void applyTableStyle(QTableWidget* table);
    void applyJobApplyButtonStyle(QPushButton* button);

private:
    QNetworkAccessManager* m_networkManager;
};
