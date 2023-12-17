// mainmenupage.h
#ifndef MAINMENUPAGE_H
#define MAINMENUPAGE_H

#include <QPushButton>
#include <QWidget>

class MainMenuPage : public QWidget
{
    Q_OBJECT

public:
    MainMenuPage(QWidget* parent = nullptr);

signals:
    void newGameClicked();
    void exitClicked();
};

#endif // MAINMENUPAGE_H
