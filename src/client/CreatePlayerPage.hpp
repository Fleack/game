// CreatePlayerPage.hpp
#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class CreatePlayerPage : public QWidget
{
    Q_OBJECT

public:
    explicit CreatePlayerPage(QWidget* parent = nullptr);

    signals:
        void createPlayerRequested(const QString& playerName);

    private slots:
        void onCreateButtonClicked();

private:
    QLineEdit* m_nameInput;
    QPushButton* m_createButton;
};
