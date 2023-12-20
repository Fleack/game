#include "MainMenuPage.hpp"

#include <QVBoxLayout>

MainMenuPage::MainMenuPage(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QVBoxLayout(this);

    auto* newGameButton = new QPushButton("Новая игра", this);
    auto* exitButton = new QPushButton("Выход", this);

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("MainMenuPage {"
                  "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #2C3E50, stop:1 #34495E);"
                  "}");

    applyButtonStyle(newGameButton);
    applyButtonStyle(exitButton);

    newGameButton->setFixedWidth(300);
    exitButton->setFixedWidth(300);

    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    layout->addWidget(newGameButton, 0, Qt::AlignHCenter);
    layout->addWidget(exitButton, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    connect(newGameButton, &QPushButton::clicked, this, &MainMenuPage::newGameClicked);
    connect(exitButton, &QPushButton::clicked, this, &MainMenuPage::exitClicked);
}

void MainMenuPage::applyButtonStyle(QPushButton* button)
{
    button->setStyleSheet("QPushButton {"
                          "    background-color: #3498DB;"
                          "    border: none;"
                          "    color: white;"
                          "    padding: 10px 20px;"
                          "    font-size: 16px;"
                          "    border-radius: 4px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #2980B9;"
                          "    color: white;"
                          "    border: 1px solid #3498DB;"
                          "}");

    button->setFixedWidth(200);
}
