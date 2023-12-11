add_executable(Game main.cpp)

add_subdirectory(server)
add_subdirectory(client)

target_link_libraries(Game PRIVATE server)
target_link_libraries(Game PRIVATE client)
