add_subdirectory(Activities)

add_library(server_lib
        Player.cpp
        PlayerManager.cpp
        Server.cpp
        Session.cpp
        WorldManager.cpp
        )

target_link_libraries(server_lib PRIVATE activities)