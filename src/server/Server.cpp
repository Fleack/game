#include "Server.hpp"

#include "Activities/EntertainmentActivity.hpp"
#include "Logger.hpp"
#include "Player.hpp"

#include <nlohmann/json.hpp>

Server::Server(asio::io_context& ioContext, uint8_t port)
    : m_acceptor{ioContext, {tcp_t::v4(), port}}
    , m_socket{ioContext}
{}

void Server::start()
{
    m_acceptor.async_accept(m_socket, [this](std::error_code const& ec) {
        if (!ec)
        {
            handleRequest();
            start();
        }
        else
        {
            LOG(error) << "Error accepting connection: " << ec.message() << std::endl;
        }
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

        auto command = jsonRequest["command"].get<std::string>();
        if (command == "create_player")
        {
            handleCreatePlayerRequest(jsonRequest);
        }
        else if (command == "pass_year")
        {
            handlePassYearRequest(jsonRequest);
        }
        else if (command == "entertainment_a ctivity")
        {
            handleEntertainmentActivityRequest(jsonRequest);
        }
        else if (command == "education_activity")
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
        else if (command == "get_player_stats")
        {
            handleGetPlayerStats();
        }
        else if (command == "get_jobs")
        {
            handleGetJobs();
        }
        else
        {
            LOG(error) << "Unknown command: " << command << std::endl;

            sendResponse(R"({"error": "Bad Request: Unknown command"})", status::bad_request);
        }
    }
    catch (json_t::exception const& e)
    {
        LOG(error) << "Error parsing JSON in handleRequest: " << e.what();

        sendResponse(R"({"error": "Bad Request: Missing required field or incorrect field type"})", status::bad_request);
    }
    catch (std::exception const& e)
    {
        LOG(error) << "Error handling request: " << e.what() << std::endl;

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handleCreatePlayerRequest(json_t const& jsonRequest)
{
    using namespace beast::http;

    try
    {
        auto playerName = jsonRequest["player_name"].get<std::string>();
        if (m_playerManager.createPlayer(jsonRequest))
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
        LOG(error) << "Error parsing JSON in handleCreatePlayerRequest: " << e.what();

        sendResponse(R"({"error": "Bad Request: Missing required field or incorrect field type"})", status::bad_request);
    }
    catch (std::exception const& e)
    {
        LOG(error) << "Error handling create player request: " << e.what();

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handlePassYearRequest(json_t const&)
{
    using namespace beast::http;

    try
    {
        m_playerManager.passYear();

        // Removing random amount of jobs
        uint8_t rnd = rand() % MAX_RANDOM_JOBS;
        for (uint8_t i = 0; i < rnd; ++i)
        {
            m_worldManager.removeRandomJob();
        }

        // Adding random amount of new jobs
        rnd = rand() % MAX_RANDOM_JOBS;
        for (uint8_t i = 0; i < rnd; ++i)
        {
            m_worldManager.addNewRandomJob();
        }

        sendResponse(R"({"message": "Year passed successfully"})", status::ok);
    }
    catch (std::exception const& e)
    {
        LOG(error) << "Error handling pass year request: " << e.what();

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handleEntertainmentActivityRequest(json_t const&)
{
    using namespace beast::http;

    try
    {
        static EntertainmentActivity const activity;
        m_playerManager.performActivity(activity);

        sendResponse(R"({"message": "Entertainment activity performed successfully"})", status::ok);
    }
    catch (std::exception const& e)
    {
        LOG(error) << "Error handling entertainment activity request: " << e.what();

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handleEducationActivityRequest(json_t const& jsonRequest)
{
    using namespace beast::http;

    try
    {
        auto const courseName = jsonRequest["course_name"].get<std::string>();

        if (m_playerManager.performEducationCourse(courseName))
        {
            sendResponse(R"({"message": "Education course performed successfully"})", status::ok);
        }
        else
        {
            sendResponse(R"({"error": "Incorrect course name"})", status::bad_request);
        }
    }
    catch (json_t::exception const& e)
    {
        LOG(error) << "Error parsing JSON in handleEducationActivityRequest: " << e.what();

        sendResponse(R"({"error": "Bad Request: Missing required field or incorrect field type"})", status::bad_request);
    }
    catch (std::exception const& e)
    {
        LOG(error) << "Error handling education activity request: " << e.what();

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handlePreformJobRequest()
{
    using namespace beast::http;

    try
    {
        m_playerManager.performJob();

        sendResponse(R"({"message": "Job performed successfully"})", status::ok);
    }
    catch (std::exception const& e)
    {
        LOG(error) << "Error handling perform job request: " << e.what();

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
            LOG(info) << "Player applied for job: " << job->getName() << " [" << job->getID() << "]";
            m_playerManager.getPlayer()->setJob(std::move(job));

            sendResponse(R"({"message": "Job applied successfully"})", status::ok);
        }
        else
        {
            LOG(error) << "Job not found with ID: " << jobId;

            sendResponse(R"({"error": "Bad Request: Incorrect job ID"})", status::bad_request);
        }
    }
    catch (json_t::exception const& e)
    {
        LOG(error) << "Error parsing JSON in handleApplyJobRequest: " << e.what();

        sendResponse(R"({"error": "Bad Request: Missing required field or incorrect field type"})", status::bad_request);
    }
    catch (std::exception const& e)
    {
        LOG(error) << "Error handling apply job request: " << e.what();

        sendResponse(R"({"error": "Internal Server Error"})", status::internal_server_error);
    }
}

void Server::handleGetPlayerStats()
{
    try
    {
        if (auto const player = m_playerManager.getPlayer())
        {
            json_t jsonResponse;
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
            LOG(error) << "Player not found.";

            sendResponse(R"({"error": "Player not found."})", beast::http::status::not_found);
        }
    }
    catch (std::exception const& e)
    {
        LOG(error) << "Error handling get player stats request: " << e.what();

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
        LOG(error) << "Error handling get jobs request: " << e.what();

        sendResponse(R"({"error": "Internal Server Error"})", beast::http::status::internal_server_error);
    }
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

    beast::http::write(m_socket, rsp);
}
