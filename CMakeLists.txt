cmake_minimum_required(VERSION 3.5)

project(dslr-webcam LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(dslr-webcam
    src/gphoto/camerahandler.cpp
    src/gstreamer/gstreamercontroller.cpp
    src/streamers/camerastreamer.cpp 
    src/gphoto/gphoto.cpp
    src/gui/mainwindow.cpp
    src/gui/mainwindow.ui
    src/main.cpp
    src/gphotocontroller.cpp
)

target_link_libraries(dslr-webcam PRIVATE Qt5::Widgets gphoto2 gphoto2_port)
