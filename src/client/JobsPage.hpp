// jobs_page.hpp
#ifndef JOBS_PAGE_HPP
#define JOBS_PAGE_HPP

#include <QNetworkAccessManager>
#include <QWidget>

class JobsPage : public QWidget
{
    Q_OBJECT

public:
    explicit JobsPage(QWidget* parent = nullptr);

signals:
    void backToPlayerPageClicked();

private slots:
    void onBackClicked();
    void onApplyJobClicked(int jobId);
    void onQuitJobClicked();

private:
    void fetchJobs();
    void processJobs(QJsonDocument const& jsonDocument);
    void fetchPlayerJob();
    void processPlayerJob(QJsonDocument const& jsonDocument);
    void hideQuitJobButton(bool);
    void showVacanciesTable();
    void onWorkClicked();

    QNetworkAccessManager* networkManager;
};

#endif // JOBS_PAGE_HPP
