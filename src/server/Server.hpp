#pragma once

#include "PlayerManager.hpp"
#include "WorldManager.hpp"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <nlohmann/json.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
using tcp_t = asio::ip::tcp;
using json_t = nlohmann::json;

class Server
{
public:
    Server(asio::io_context&, uint16_t port);

    void start();

private:
    void handleRequest();

    void handleCreatePlayerRequest(json_t const&);
    void handlePassYearRequest(json_t const&);
    void handleEntertainmentActivityRequest(json_t const&);
    void handleEducationActivityRequest(json_t const&);
    void handlePreformJobRequest();
    void handleApplyJobRequest(json_t const&);
    void handleQuitJob();
    void handleGetPlayerStats();
    void handleGetPlayerSkills();
    void handleGetJobs();
    void handleGetPlayerJob();
    void handleTerminateSession();

    void sendResponse(std::string const& /* body */, beast::http::status);

private:
    static constexpr uint8_t MAX_RANDOM_JOBS = 6;
    static constexpr uint8_t HTTP_VERSION = 11;

    bool m_terminate{false};

    asio::ip::tcp::acceptor m_acceptor;
    asio::ip::tcp::socket m_socket;
    PlayerManager m_playerManager{};
    WorldManager m_worldManager{};
};
