// characterpage.cpp
#include "CharacterPage.hpp"
#include <QVBoxLayout>
#include <QMessageBox> // Добавим заголовочный файл

CharacterPage::CharacterPage(const QString &playerName, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *nameLabel = new QLabel("Имя: " + playerName, this);
    QLabel *healthLabel = new QLabel("Здоровье: 100", this);
    QLabel *energyLabel = new QLabel("Энергия: 100", this);
    QLabel *happinessLabel = new QLabel("Счастье: 100", this);
    QLabel *moneyLabel = new QLabel("Деньги: 0", this);
    QLabel *ageLabel = new QLabel("Возраст: 18", this);

    QPushButton *workButton = new QPushButton("Работа", this);
    QPushButton *skillsButton = new QPushButton("Умения", this);
    QPushButton *entertainmentButton = new QPushButton("Развлечения", this);
    QPushButton *educationButton = new QPushButton("Обучение", this);
    QPushButton *backButton = new QPushButton("Назад", this);

    layout->addWidget(nameLabel);
    layout->addWidget(healthLabel);
    layout->addWidget(energyLabel);
    layout->addWidget(happinessLabel);
    layout->addWidget(moneyLabel);
    layout->addWidget(ageLabel);

    layout->addWidget(workButton);
    layout->addWidget(skillsButton);
    layout->addWidget(entertainmentButton);
    layout->addWidget(educationButton);
    layout->addWidget(backButton);

    connect(workButton, &QPushButton::clicked, this, &CharacterPage::workClicked);
    connect(skillsButton, &QPushButton::clicked, this, &CharacterPage::skillsClicked);
    connect(entertainmentButton, &QPushButton::clicked, this, &CharacterPage::entertainmentClicked);
    connect(educationButton, &QPushButton::clicked, this, &CharacterPage::educationClicked);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        // Добавим подтверждающий диалог
        QMessageBox msgBox(
            QMessageBox::Question,
            "Вернуться в главное меню",
            "Вы уверены, что хотите вернуться в главное меню?",
            QMessageBox::Yes | QMessageBox::No,
            this
        );
        msgBox.setDefaultButton(QMessageBox::No);

        int ret = msgBox.exec();
        if (ret == QMessageBox::Yes) {
            emit backToMainMenuClicked();
        }
    });
}
