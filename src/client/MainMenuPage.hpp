#pragma once

#include <QPushButton>
#include <QWidget>

class MainMenuPage final : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuPage(QWidget* parent = nullptr);

signals:
    void newGameClicked();
    void exitClicked();

private:
    static void applyButtonStyle(QPushButton* button);
};
