include_directories(.)

add_subdirectory(Activities)

add_library(server
        Server.cpp
        Logger.cpp
        Player.cpp
        PlayerManager.cpp
        WorldManager.cpp
)
