#pragma once

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>

#define LOG(LEVEL) BOOST_LOG_TRIVIAL(LEVEL)

class Logger
{
public:
    static Logger& instance();
    void initialize();

private:
    Logger();
    ~Logger();

    friend class Server;
};
