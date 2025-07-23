cmake_minimum_required(VERSION 3.16)

project(MediaPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)
find_package(Qt6 REQUIRED COMPONENTS MultimediaWidgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

set(PROJECT_SOURCES_MODELS
    srcs/models/MediaPlayerM.hpp srcs/models/MediaPlayerM.cpp
    srcs/models/AudioFileM.hpp srcs/models/AudioFileM.cpp
    srcs/models/TracksTableM.hpp srcs/models/TracksTableM.cpp
)

set(PROJECT_SOURCES_VIEWS
    srcs/views/MediaPlayerV.hpp srcs/views/MediaPlayerV.cpp
    srcs/views/PlayListV.hpp srcs/views/PlayListV.cpp
    srcs/views/PlayerV.hpp srcs/views/PlayerV.cpp
    srcs/views/PlayerButtonsV.hpp srcs/views/PlayerButtonsV.cpp
    srcs/views/PlayListButtonsV.hpp srcs/views/PlayListButtonsV.cpp
    srcs/views/PlayScreenV.hpp srcs/views/PlayScreenV.cpp
    srcs/views/ScreenV.hpp srcs/views/ScreenV.cpp
)

set(PROJECT_SOURCES_CONTROLLERS
    srcs/controllers/MediaPlayerC.hpp srcs/controllers/MediaPlayerC.cpp
)

set(PROJECT_SOURCES
        srcs/main.cpp
        srcs/mainwindow.hpp srcs/mainwindow.cpp
        ${PROJECT_SOURCES_MODELS}
        ${PROJECT_SOURCES_VIEWS}
        ${PROJECT_SOURCES_CONTROLLERS}
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MediaPlayer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MediaPlayer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MediaPlayer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MediaPlayer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MediaPlayer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(MediaPlayer PRIVATE Qt6::Multimedia)
target_link_libraries(MediaPlayer PRIVATE Qt6::MultimediaWidgets)
target_link_libraries(MediaPlayer PRIVATE Qt6::Widgets)
target_link_libraries(MediaPlayer PRIVATE Qt6::Core)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MediaPlayer)
endif()
set_target_properties(MediaPlayer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MediaPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MediaPlayer)
endif()
