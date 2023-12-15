#pragma once

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onStartGameClicked();
    void onExitClicked();

private:
    void setupUI();

    QPushButton* m_startGameButton;
    QPushButton* m_exitButton;
    QVBoxLayout* m_mainLayout;
    QNetworkAccessManager* m_networkManager;
};
