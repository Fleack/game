#pragma once
#include "PlayerManager.hpp"
#include "WorldManager.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/http/status.hpp>
#include <nlohmann/json.hpp>

class Server;
namespace asio = boost::asio;
namespace beast = boost::beast;
using tcp_t = asio::ip::tcp;
using json_t = nlohmann::json;

class Session
{
public:
    explicit Session(asio::ip::tcp::socket, PlayerManager&, WorldManager&, Server&);

    void handleRequest();

private:
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
    static constexpr uint8_t MAX_RANDOM_JOBS = 4;
    static constexpr uint8_t HTTP_VERSION = 11;

    asio::ip::tcp::socket m_socket;
    Server& m_server;

    PlayerManager& m_playerManager;
    WorldManager& m_worldManager;
};
