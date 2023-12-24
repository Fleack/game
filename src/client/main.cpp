#include "MainWindow.hpp"

#include <iostream>
#include <QApplication>

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "Client is running..." << std::endl;
        QApplication app(argc, argv);
        MainWindow menu;
        menu.show();

        int const result = app.exec();
        return result;
    }
    catch (std::exception const& e)
    {
        std::cerr << "Exception in client: " << e.what() << std::endl;
        return -1;
    }
}
