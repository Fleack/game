# Qt6
set(CMAKE_PREFIX_PATH "/usr/include/x86_64-linux-gnu/qt6")
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
include_directories(${Qt6Core_INCLUDE_DIRS} ${Qt6Gui_INCLUDE_DIRS} ${Qt6Widgets_INCLUDE_DIRS})

add_library(client Client.cpp Client.hpp)
target_link_libraries(client PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
