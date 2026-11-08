cmake_minimum_required(VERSION 3.21)
project(Project2 LANGUAGES C CXX)

#SFML 3
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Downloads & builds SFML automatically
include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
)

FetchContent_MakeAvailable(SFML)

#download for json parsing
FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(nlohmann_json)

#Project files/classes
add_executable(Project2
        main.cpp

        Red_Black.cpp
        Red_Black.h

        Hash_Table.cpp
        Hash_Table.h

        Display.cpp
        Display.h

        Analyzer.cpp
        Analyzer.h

        Data_Loader.cpp
        Data_Loader.h

        Data_Generator.cpp
        Data_Generator.h
)

target_link_libraries(Project2 PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    nlohmann_json::nlohmann_json
)

if(WIN32)
    target_link_libraries(Project2 PRIVATE comdlg32)
endif()


