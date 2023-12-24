add_subdirectory(Activities)
add_library(server
        main.cpp
        Session.cpp
        Server.cpp
        Player.cpp
        PlayerManager.cpp
        WorldManager.cpp
)

target_link_libraries(server PRIVATE activities)

target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
