// playerskillspage.hpp
#ifndef PLAYERSKILLSPAGE_HPP
#define PLAYERSKILLSPAGE_HPP

#include <QWidget>
#include <QNetworkAccessManager>

class PlayerSkillsPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerSkillsPage(QWidget* parent = nullptr);

    signals:
        void backToMainMenuClicked();

    private slots:
        void onBackClicked();
    void fetchPlayerSkills();

private:
    QNetworkAccessManager* networkManager;
};

#endif // PLAYERSKILLSPAGE_HPP
