add_subdirectory(Activities)
add_library(server
        Server.cpp
        Logger.cpp
        Player.cpp
        PlayerManager.cpp
        WorldManager.cpp
)

target_include_directories(server PRIVATE activities)
