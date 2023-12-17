// playerskillspage.hpp
#ifndef PLAYERSKILLSPAGE_HPP
#define PLAYERSKILLSPAGE_HPP

#include <QNetworkAccessManager>
#include <QWidget>

class PlayerSkillsPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerSkillsPage(QWidget* parent = nullptr);

signals:
    void backToPlayerPageClicked();

private slots:
    void onBackClicked();
    void fetchPlayerSkills();

private:
    QNetworkAccessManager* networkManager;
};

#endif // PLAYERSKILLSPAGE_HPP
