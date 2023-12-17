// jobspage.h
#ifndef JOBSPAGE_H
#define JOBSPAGE_H

#include <QNetworkAccessManager>
#include <QWidget>

class JobsPage : public QWidget
{
    Q_OBJECT

public:
    explicit JobsPage(QWidget* parent = nullptr);

signals:
    void backToPlayerPageClicked();

public slots:
    void onBackClicked();
    void onApplyJobClicked(int jobId);

private:
    void fetchJobs();
    void processJobs(const QJsonDocument& jsonDocument);

private:
    QNetworkAccessManager* networkManager;
};

#endif // JOBSPAGE_H
