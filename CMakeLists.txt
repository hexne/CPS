cmake_minimum_required(VERSION 3.30)
project(CPS)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(Modules)
target_sources(Modules
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        Param.cppm
        LexicalAnalysis.cppm
)


find_package(Qt6 COMPONENTS
    Core
    REQUIRED
)

add_executable(CPS main.cpp)
target_link_libraries(CPS
    Qt::Core
    Modules
)

