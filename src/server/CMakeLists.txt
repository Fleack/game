add_subdirectory(src)

add_executable(server
        main.cpp
)

target_link_libraries(server PRIVATE server_lib)

target_include_directories(server PRIVATE src)
