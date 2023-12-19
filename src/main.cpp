#include "client/MainWindow.hpp"
#include "server/Server.hpp"

#include <iostream>
#include <QApplication>
#include <QThread>

void runServer()
{
    try
    {
        asio::io_context io_context;
        Server server(io_context, 12345);
        std::cout << "Server is running..." << std::endl;
        server.start();
        io_context.run();
    }
    catch (std::exception const& e)
    {
        std::cerr << "Exception in server: " << e.what() << std::endl;
        return;
    }
}

int runClient(int argc, char* argv[])
{
    try
    {
        std::cout << "Client is running..." << std::endl;
        QApplication app(argc, argv);
        MainWindow menu;
        menu.show();

        int result = app.exec();
        return result;
    }
    catch (std::exception const& e)
    {
        std::cerr << "Exception in client: " << e.what() << std::endl;
        return -1;
    }
}

int main(int argc, char* argv[])
{
    std::thread serverThread(runServer);
    int result = runClient(argc, argv);

    serverThread.join();

    return result;
}
