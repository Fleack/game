# Qt6
set(CMAKE_PREFIX_PATH "/usr/include/x86_64-linux-gnu/qt6")
find_package(Qt6 COMPONENTS Core Gui Widgets Network REQUIRED)
include_directories(${Qt6Core_INCLUDE_DIRS} ${Qt6Gui_INCLUDE_DIRS} ${Qt6Widgets_INCLUDE_DIRS} ${Qt6Network_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

add_subdirectory(src)

add_executable(client
        main.cpp)

target_include_directories(client PRIVATE src)
target_link_libraries(client PRIVATE client_lib)
target_link_libraries(client PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)
