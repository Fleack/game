#include "server/Server.hpp"

#include <iostream>
#include <thread>

void runServer()
{
    try
    {
        asio::io_context io_context;
        Server server(io_context, 12345);
        server.start();
        io_context.run();

    }
    catch (std::exception const& e)
    {
        std::cerr << "Exception in server: " << e.what() << std::endl;
        return;
    }
}

void runClient()
{
    std::cout << "Client is running..." << std::endl;
}

int main()
{
    std::thread serverThread(runServer);
    runClient();
    serverThread.join();

    return 0;
}
