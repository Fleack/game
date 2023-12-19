// entertainmentpage.hpp
#ifndef ENTERTAINMENTPAGE_HPP
#define ENTERTAINMENTPAGE_HPP

#include <QNetworkAccessManager>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class EntertainmentPage : public QWidget
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

private:
    QNetworkAccessManager* networkManager;
};

#endif // ENTERTAINMENTPAGE_HPP
