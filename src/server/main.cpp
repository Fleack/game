#include "Server.hpp"

#include <iostream>

int main()
{
    try
    {
        Server server(12345);
        std::cout << "Server is running..." << std::endl;
        server.start();
        server.startCtx();
    }
    catch (std::exception const& e)
    {
        std::cerr << "Exception in server: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}