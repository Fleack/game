// CreatePlayerPage.cpp
#include "CreatePlayerPage.hpp"
#include <QVBoxLayout>

CreatePlayerPage::CreatePlayerPage(QWidget* parent)
    : QWidget(parent)
{
    m_nameInput = new QLineEdit(this);
    m_createButton = new QPushButton("Создать", this);

    connect(m_createButton, &QPushButton::clicked, this, &CreatePlayerPage::onCreateButtonClicked);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_nameInput);
    layout->addWidget(m_createButton);
}
