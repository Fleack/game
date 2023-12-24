find_package(Qt6 COMPONENTS Core Gui Widgets Network Test REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(client_tests
        main.cpp
        CreatePlayerPage.hpp
        PlayerPage.hpp
        MainMenuPage.hpp
        JobsPage.hpp
        PlayerSkillsPage.hpp
        EntertainmentPage.hpp
        EducationPage.hpp
)

target_link_libraries(client_tests PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network Qt6::Test)
target_link_libraries(client_tests PRIVATE client)

target_include_directories(client_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
