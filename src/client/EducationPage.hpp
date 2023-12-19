// educationpage.hpp
#ifndef EDUCATIONPAGE_HPP
#define EDUCATIONPAGE_HPP

#include <QNetworkAccessManager>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class EducationPage : public QWidget
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

private:
    QNetworkAccessManager* networkManager;
};

#endif // EDUCATIONPAGE_HPP
