cmake_minimum_required(VERSION 3.0.0)
project(LogReader VERSION 0.1.0 LANGUAGES C CXX)

if(DEFINED QTDIR)
    list(APPEND CMAKE_PREFIX_PATH "${QTDIR}")
elseif(DEFINED ENV{QTDIR})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{QTDIR}")
else()
    message(WARNING "QTDIR not defined! usage: cmake -DQTDIR=[path to qt]")
    return()
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOUIC TRUE)
set(CMAKE_AUTORCC TRUE)
set(CMAKE_AUTOMOC TRUE)

if (MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

    add_compile_options(/wd4251 /wd4275)
    add_definitions(-DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS -DNOMINMAX)
endif(MSVC)

add_executable(LogReader
    static/static.qrc

    main.cpp
    window.cpp
    qss_loader.cpp
    log_item_delegate.cpp
    log_page.cpp
    log_name_dialog.cpp
)

target_link_libraries(LogReader
    Qt5::Widgets
)