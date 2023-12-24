add_executable(server_tests
        main.cpp
        WorldManager.cpp
        PlayerManager.cpp
        Player.cpp
)

target_link_libraries(server_tests PRIVATE gtest gtest_main)
target_link_libraries(server_tests PRIVATE server activities)

target_include_directories(server_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})