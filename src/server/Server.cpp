#include "Server.hpp"

#include "Session.hpp"

#include <iostream>

Server::Server(uint16_t port)
    : m_acceptor{m_ioContext, {tcp_t::v4(), port}}
    , m_socket{m_ioContext}
    , m_timer{m_ioContext, std::chrono::seconds(TIMER_DURATION_SECONDS)}
{
    startTimer();
}

// Переделать под сессию с мувом сокета       | Done
// Добавить тесты GTest+QTest                 |
// Разделить на два бинаря сервер/клиент      | Done
// Пофиксить SEGFAULT на кнопке "Развлечения" | Done
// Пофиксить выключение клиента и сервера     | Done
// Добавить таймер                            | Done

void Server::startCtx()
{
    m_ioContext.run();
}

void Server::start()
{
    m_acceptor.async_accept(m_socket, [this](std::error_code const& ec) {
        if (!ec)
        {
            Session session(std::move(m_socket), m_playerManager, m_worldManager, *this);
            session.handleRequest();
        }
        else
        {
            std::cout << "Error accepting connection: " << ec.message() << std::endl;
        }

        start();
    });
}

void Server::resetTimer()
{
    m_timer.cancel();
    startTimer();
}

void Server::startTimer()
{
    m_timer.async_wait([this](const boost::system::error_code&) {
        terminateServer();
    });
}

void Server::terminateServer()
{
    exit(0);
}
