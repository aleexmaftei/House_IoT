cmake_minimum_required(VERSION 3.6)
project(House_IoT)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

add_executable(House_IoT
        project/src/main.cpp
        project/src/configuration/serverConfiguration.cpp
        project/src/handlers/curtainsHandler.cpp
        project/src/handlers/testConnectionHandler.cpp
        project/src/handlers/automaticDoorLockHandler.cpp)

target_link_libraries(House_IoT PkgConfig::Pistache)
