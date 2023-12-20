#include "Server.hpp"

#include "Activities/EntertainmentActivity.hpp"
#include "Player.hpp"

#include <iostream>

#include <magic_enum/magic_enum.hpp>
#include <nlohmann/json.hpp>

Server::Server(asio::io_context& ioContext, uint16_t port)
    : m_acceptor{ioContext, {tcp_t::v4(), port}}
    , m_socket{ioContext}
{
}

void Server::start()
{
    m_acceptor.async_accept(m_socket, [this](std::error_code const& ec) {
        if (!ec)
        {
            handleRequest();
        }
        else
        {
            std::cout << "Error accepting connection: " << ec.message() << std::endl;
        }

        m_socket.close();
        start();
    });
}

void Server::handleRequest()
{
    using namespace beast::http;

    try
    {
        beast::flat_buffer buffer;
        request<string_body> req;
        read(m_socket, buffer, req);

        auto jsonRequest = json_t::parse(req.body());
        std::cout << "\n---------------------------------------------------------\n";
        std::cout << "Recieved request: " << jsonRequest << std::endl;
        std::cout << "---------------------------------------------------------\n\n";

        auto command = jsonRequest["command"].get<std::string>();
        if (command == "create_player")
        {
            handleCreatePlayerRequest(jsonRequest);
        }
        else if (command == "pass_year")
        {
            handlePassYearRequest(jsonRequest);
        }
        else if (command == "perform_entertainment_activity")
        {
            handleEntertainmentActivityRequest(jsonRequest);
        }
        else if (command == "perform_education_activity")
        {
            handleEducationActivityRequest(jsonRequest);
        }
        else if (command == "perform_job")
        {
            handlePreformJobRequest();
        }
        else if (command == "apply_job")
        {
            handleApplyJobRequest(jsonRequest);
        }
        else if (command == "quit_job")
        {
            handleQuitJob();
        }
        else if (command == "get_player_stats")
        {
            handleGetPlayerStats();
        }
        else if (command == "get_player_skills")
        {
            handleGetPlayerSkills();
        }
        else if (command == "get_jobs")
        {
            handleGetJobs();
        }
        else if (command == "get_player_job")
        {
            handleGetPlayerJob();
        }
        else if (command == "terminate_session")
        {
            handleTerminateSession();
        }
        else
        {
            std::cout << "Unknown command: " << command << std::endl;

            sendResponse(R"({"error": "Bad Request: Unknown command"})", status::bad_request);
        }
    }
    catch (json_t::exception const& e)
    {
        std::cout << "Error parsing JSON in handleRequest: " << e.what();

        sendResponse(R"({"error": "Bad Request: Missing required field or incorrect field type"})", status::bad_request);
    }
    catch (std::exception const& e)
    {
        std::cout << "Error handling request: " << e.what() << std::endl;

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handleCreatePlayerRequest(json_t const& jsonRequest)
{
    using namespace beast::http;

    try
    {
        auto const playerName = jsonRequest["player_name"].get<std::string>();
        if (m_playerManager.createPlayer(playerName))
        {
            sendResponse(R"({"message": "Player created successfully"})", status::created);
        }
        else
        {
            sendResponse(R"({"error": "Failed to create player"})", status::internal_server_error);
        }
    }
    catch (json_t::exception const& e)
    {
        std::cout << "Error parsing JSON in handleCreatePlayerRequest: " << e.what() << std::endl;

        sendResponse(R"({"error": "Bad Request: Missing required field or incorrect field type"})", status::bad_request);
    }
    catch (std::exception const& e)
    {
        std::cout << "Error handling create player request: " << e.what() << std::endl;

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handlePassYearRequest(json_t const&)
{
    using namespace beast::http;

    try
    {
        m_playerManager.passYear();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dist(0, MAX_RANDOM_JOBS);
        for (uint8_t i = 0; i < dist(gen); ++i)
        {
            m_worldManager.addNewRandomJob();
        }

        for (uint8_t i = 0; i < dist(gen); ++i)
        {
            m_worldManager.removeRandomJob();
        }

        sendResponse(R"({"message": "Year passed successfully"})", status::ok);
    }
    catch (std::exception const& e)
    {
        std::cout << "Error handling pass year request: " << e.what() << std::endl;

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handleQuitJob()
{
    if (m_playerManager.getPlayer()->removeJob())
    {
        sendResponse(R"({"message": "Job successfully removed"})", beast::http::status::ok);
    }
    else
    {
        sendResponse(R"({"error": "No job to quit"})", beast::http::status::not_modified);
    }
}

void Server::handleGetPlayerJob()
{
    try
    {
        if (auto const player = m_playerManager.getPlayer())
        {
            json_t jsonResponse;
            if (auto const job = player->getJob())
            {
                json_t jobInfo;
                jobInfo["id"] = job->getID();
                jobInfo["name"] = job->getName();
                jobInfo["salary"] = job->getSalary();
                jobInfo["energy_decrease"] = job->getEnergy();
                jobInfo["health_decrease"] = job->getHealth();
                jobInfo["happiness_decrease"] = job->getHappienes();
                jsonResponse["job"] = jobInfo;
            }

            sendResponse(jsonResponse.dump(), beast::http::status::ok);
        }
        else
        {
            std::cout << "Player not found" << std::endl;

            sendResponse(R"({"error": "Player not found."})", beast::http::status::not_found);
        }
    }
    catch (std::exception const& e)
    {
        std::cout << "Error handling get player stats request: " << e.what() << std::endl;

        sendResponse(R"({"error": "Internal Server Error"})", beast::http::status::internal_server_error);
    }
}

void Server::handleEntertainmentActivityRequest(json_t const&)
{
    using namespace beast::http;

    try
    {
        EntertainmentActivity activity;
        if (m_playerManager.performEntertainmentActivity(activity))
        {
            sendResponse(R"({"message": "Entertainment activity performed successfully"})", status::ok);
        }
        else
        {
            sendResponse(R"({"error": "Player doesn't have enough money"})", status::bad_request);
        }
    }
    catch (std::exception const& e)
    {
        std::cout << "Error handling entertainment activity request: " << e.what() << std::endl;

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handleEducationActivityRequest(json_t const& jsonRequest)
{
    using namespace beast::http;

    try
    {
        // auto const courseName = jsonRequest["course_name"].get<std::string>();

        if (m_playerManager.performEducationCourse(""))
        {
            sendResponse(R"({"message": "Education course performed successfully"})", status::ok);
        }
        else
        {
            sendResponse(R"({"error": "Not enoght money"})", status::bad_request);
        }
    }
    catch (json_t::exception const& e)
    {
        std::cout << "Error parsing JSON in handleEducationActivityRequest: " << e.what() << std::endl;

        sendResponse(R"({"error": "Bad Request: Missing required field or incorrect field type"})", status::bad_request);
    }
    catch (std::exception const& e)
    {
        std::cout << "Error handling education activity request: " << e.what() << std::endl;

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handlePreformJobRequest()
{
    using namespace beast::http;
    using enum perform_job_error_e;
    try
    {
        perform_job_error_e error = m_playerManager.performJob();
        if (error == OK)
        {
            sendResponse(R"({"message": "Job performed successfully"})", status::ok);
        }
        else if (error == ENERGY)
        {
            sendResponse(R"({"error": "Not enough energy"})", status::bad_request);
        }
        else if (error == HEALTH)
        {
            sendResponse(R"({"error": "Not enough health"})", status::bad_request);
        }
        else if (error == HAPPINESS)
        {
            sendResponse(R"({"error": "Not enough happiness"})", status::bad_request);
        }
        else
        {
            sendResponse(R"({"error": "Unknown error"})", status::bad_request);
        }
    }
    catch (std::exception const& e)
    {
        std::cout << "Error handling perform job request: " << e.what() << std::endl;

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handleApplyJobRequest(json_t const& jsonRequest)
{
    using namespace beast::http;

    try
    {
        uint32_t const jobId = jsonRequest["job_id"].get<uint32_t>();

        if (auto job = m_worldManager.moveJob(jobId))
        {
            std::cout << "Player applied for job: " << job->getName() << " [" << job->getID() << "]" << std::endl;
            m_playerManager.getPlayer()->setJob(std::move(job));

            sendResponse(R"({"message": "Job applied successfully"})", status::ok);
        }
        else
        {
            std::cout << "Job not found with ID: " << jobId << std::endl;

            sendResponse(R"({"error": "Bad Request: Incorrect job ID"})", status::bad_request);
        }
    }
    catch (json_t::exception const& e)
    {
        std::cout << "Error parsing JSON in handleApplyJobRequest: " << e.what() << std::endl;

        sendResponse(R"({"error": "Bad Request: Missing required field or incorrect field type"})", status::bad_request);
    }
    catch (std::exception const& e)
    {
        std::cout << "Error handling apply job request: " << e.what() << std::endl;

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handleGetPlayerSkills()
{
    try
    {
        if (auto const player = m_playerManager.getPlayer())
        {
            json_t skillsArray;

            auto const stats = player->getSkills();

            for (auto const& [skill, value] : stats)
            {
                json_t skillInfo;
                skillInfo["name"] = magic_enum::enum_name(skill);
                skillInfo["value"] = value;
                skillsArray.push_back(skillInfo);
            }

            sendResponse(skillsArray.dump(), beast::http::status::ok);
        }
        else
        {
            std::cout << "Player not found" << std::endl;
            sendResponse(R"({"error": "Player not found."})", beast::http::status::not_found);
        }
    }
    catch (std::exception const& e)
    {
        std::cout << "Error handling get player stats request: " << e.what() << std::endl;
        sendResponse(R"({"error": "Internal Server Error"})", beast::http::status::internal_server_error);
    }
}

void Server::handleGetPlayerStats()
{
    try
    {
        if (auto const player = m_playerManager.getPlayer())
        {
            json_t jsonResponse;
            jsonResponse["name"] = player->getName();
            jsonResponse["health"] = player->getHealth();
            jsonResponse["energy"] = player->getEnergy();
            jsonResponse["happiness"] = player->getHappiness();
            jsonResponse["age"] = player->getAge();
            jsonResponse["money"] = player->getMoney();

            if (auto const job = player->getJob())
            {
                json_t jobInfo;
                jobInfo["id"] = job->getID();
                jobInfo["name"] = job->getName();
                jobInfo["salary"] = job->getSalary();
                jobInfo["energy_decrease"] = job->getEnergy();
                jobInfo["health_decrease"] = job->getHealth();
                jobInfo["happiness_decrease"] = job->getHappienes();
                jsonResponse["job"] = jobInfo;
            }

            sendResponse(jsonResponse.dump(), beast::http::status::ok);
        }
        else
        {
            std::cout << "Player not found" << std::endl;

            sendResponse(R"({"error": "Player not found."})", beast::http::status::not_found);
        }
    }
    catch (std::exception const& e)
    {
        std::cout << "Error handling get player stats request: " << e.what() << std::endl;

        sendResponse(R"({"error": "Internal Server Error"})", beast::http::status::internal_server_error);
    }
}

void Server::handleGetJobs()
{
    try
    {
        json_t jsonResponse;
        for (auto const& job : m_worldManager.getAllJobs())
        {
            json_t jobInfo;
            jobInfo["id"] = job->getID();
            jobInfo["name"] = job->getName();
            jobInfo["salary"] = job->getSalary();
            jobInfo["energy_decrease"] = job->getEnergy();
            jobInfo["health_decrease"] = job->getHealth();
            jobInfo["happiness_decrease"] = job->getHappienes();
            jsonResponse["jobs"].push_back(jobInfo);
        }

        sendResponse(jsonResponse.dump(), beast::http::status::ok);
    }
    catch (std::exception const& e)
    {
        std::cout << "Error handling get jobs request: " << e.what() << std::endl;

        sendResponse(R"({"error": "Internal Server Error"})", beast::http::status::internal_server_error);
    }
}

void Server::handleTerminateSession()
{
    std::cout << "Terminating server..." << std::endl;

    sendResponse(R"({"message": "Server terminating"})", beast::http::status::ok);

    m_acceptor.cancel();
    m_acceptor.close();
    m_socket.close();

    m_terminate = true;
}

void Server::sendResponse(std::string const& body, beast::http::status status)
{
    using namespace beast::http;

    response<string_body> rsp;
    rsp.version(HTTP_VERSION);
    rsp.result(status);
    rsp.set(field::server, "LifeSimulator");
    rsp.set(field::content_type, "application/json");
    rsp.body() = body;
    rsp.prepare_payload();

    std::cout << "\n---------------------------------------------------------\n";
    std::cout << "Sent response: " << rsp.result() << " | " << rsp.body() << std::endl;
    std::cout << "---------------------------------------------------------\n";

    beast::http::write(m_socket, rsp);
}
