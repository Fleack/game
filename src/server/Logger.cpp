#include "Logger.hpp"

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/console.hpp>

auto BOOST_LOG_GLOBAL_LOGGER_INIT(Logger, boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>)
{
    boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> g_log;
    boost::log::add_console_log(std::cerr, boost::log::keywords::format = "[%TimeStamp%] [%Severity%] %Message%");
    return g_log;
}

Logger::Logger()
{
    initialize();
}

Logger::~Logger()
{
    boost::log::core::get()->remove_all_sinks();
}

Logger& Logger::instance()
{
    static Logger g_logger;
    return g_logger;
}

void Logger::initialize()
{
}