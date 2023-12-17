// mainmenupage.cpp
#include "MainMenuPage.hpp"
#include <QVBoxLayout>

MainMenuPage::MainMenuPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *newGameButton = new QPushButton("Новая игра", this);
    QPushButton *exitButton = new QPushButton("Выход", this);

    layout->addWidget(newGameButton);
    layout->addWidget(exitButton);

    connect(newGameButton, &QPushButton::clicked, this, &MainMenuPage::newGameClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainMenuPage::exitClicked);
}
