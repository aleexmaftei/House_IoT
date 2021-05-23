cmake_minimum_required(VERSION 3.6)
project(House_IoT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)    #[[sudo add-apt-repository ppa:pistache+team/unstable
                                                                       sudo apt update
                                                                       sudo apt install libpistache-dev]]
pkg_check_modules(Mosquitto REQUIRED IMPORTED_TARGET libmosquitto)  #[[sudo apt-get install -y libmosquitto-dev]]
pkg_check_modules(Libuuid REQUIRED IMPORTED_TARGET uuid)            #[[sudo apt-get install uuid-dev]]

add_executable(House_IoT
        project/lib/crossguid/src/guid.cpp
        project/src/main.cpp
        project/src/configuration/serverConfiguration.cpp
        project/src/handlers/curtainsHandler.cpp
        project/src/handlers/testConnectionHandler.cpp
        project/src/handlers/secretDoorHandler.cpp
        project/src/handlers/testConnectionHandler.cpp
        project/src/handlers/automaticDoorLockHandler.cpp 
        project/src/handlers/automaticLightsHandler.cpp)
        

target_link_libraries(House_IoT PkgConfig::Pistache)
target_link_libraries(House_IoT PkgConfig::Mosquitto)
target_link_libraries(House_IoT PkgConfig::Libuuid)
target_link_libraries(House_IoT ${CMAKE_THREAD_LIBS_INIT})
target_compile_definitions(House_IoT PUBLIC GUID_LIBUUID PRIVATE GUID_LIBUUID)
