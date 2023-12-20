#pragma once

#include <QNetworkAccessManager>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>

class PlayerSkillsPage final : public QWidget
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
    void applyTableStyle(QTableWidget* table);
    void applyButtonStyle(QPushButton* button);

private:
    QNetworkAccessManager* m_networkManager;
};
