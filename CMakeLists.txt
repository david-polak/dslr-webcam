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
    src/gphoto/camerahandler.h
    src/gstreamer/gstreamercontroller.cpp
    src/gstreamer/gstreamercontroller.h
    src/streamers/camerastreamer.cpp
    src/streamers/camerastreamer.h
    src/streamers/picturestreamer.cpp
    src/streamers/picturestreamer.h
    src/streamers/istreamer.h
    src/gphoto/gphoto.cpp
    src/gphoto/gphoto.h
    src/gui/mainwindow.cpp
    src/gui/mainwindow.h
    src/gui/mainwindow.ui
    src/gui/widgetradiocontrol.cpp
    src/gui/widgetradiocontrol.h
    src/gui/widgetradiocontrol.ui
    src/camera.cpp
    src/camera.h
    src/dslrwebcam.cpp
    src/dslrwebcam.h
    src/main.cpp
)

target_link_libraries(dslr-webcam PRIVATE Qt5::Widgets gphoto2 gphoto2_port)
