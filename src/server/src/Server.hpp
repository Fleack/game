#pragma once

#include "PlayerManager.hpp"
#include "WorldManager.hpp"

#include <boost/asio.hpp>

namespace asio = boost::asio;

class Server
{
public:
    explicit Server(uint16_t port);

    void start();
    void startCtx();
    static void terminateServer();

    void resetTimer();

private:
    void startTimer();

    static constexpr std::chrono::seconds TIMER_DURATION_SECONDS{180};

    asio::io_context m_ioContext;
    asio::ip::tcp::acceptor m_acceptor;
    asio::ip::tcp::socket m_socket;
    asio::steady_timer m_timer;

    PlayerManager m_playerManager;
    WorldManager m_worldManager;
};
