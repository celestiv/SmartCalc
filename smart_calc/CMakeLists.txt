cmake_minimum_required(VERSION 3.14)
project(s21_calculator LANGUAGES CXX C)

# Set project properties
set(PROJECT_NAME s21_calculator)
set(PROJECT_VERSION_SEMANTIC 2.1.1.1)
set(PROJECT_VERSION_CPP_MIN 11)

# Set project options
# Options availables for external project start with "EXT_OPT_QCPLIB_", those options can be use in top CMakeFiles.
# All options are disabled by default.
# List of available options :
# - Currently no options available

# # Check for target architecture
# if(NOT PROJECT_ARCH_TARGET)
#     message(FATAL_ERROR "Cmake variable \"PROJECT_ARCH_TARGET\" is undefined, please set it in your root CMakelist.")
# endif()

# Set project configuration
project(${PROJECT_NAME} LANGUAGES CXX)
project(${PROJECT_NAME} VERSION "${PROJECT_VERSION_SEMANTIC}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)   # Specific to Qt
set(CMAKE_AUTOMOC ON)   # Specific to Qt
set(CMAKE_AUTORCC ON)   # Specific to Qt

# Set C++ standard to use
if(DEFINED CMAKE_CXX_STANDARD)
    if(${CMAKE_CXX_STANDARD} LESS ${PROJECT_VERSION_CPP_MIN})
        message(FATAL_ERROR "Project ${PROJECT_NAME} require at least C++ standard ${PROJECT_VERSION_CPP_MIN}")
    endif()
else()
    set(CMAKE_CXX_STANDARD ${PROJECT_VERSION_CPP_MIN})
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Project \"${PROJECT_NAME}\" compiled with C++ standard ${CMAKE_CXX_STANDARD}")

# Configure file project - File containing macro that can be used in project
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/config.h")

# Find Qt packages

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS PrintSupport REQUIRED)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport REQUIRED)


# Manage library files
set(PROJECT_HEADERS
    mainwindow.h
    creditwindow.h
    depositwindow.h
    plot.h
    qcustomplot.h
    config.h

    ../s21_smart_calc.h
)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    creditwindow.cpp
    depositwindow.cpp
    plot.cpp
    qcustomplot.cpp

    ../s21_parser.c
    ../s21_calculator.c
    ../s21_common.c
    ../credit.c
    ../deposit.c
)
        
set(PROJECT_UI
    mainwindow.ui
    creditwindow.ui
    depositwindow.ui
    plot.ui
)


set(PROJECT_FILES ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_UI} ${PROJECT_RSC})

# # Platform dependant stuff
# # Windows (for both x86/x64)
# if(WIN32)

# endif()

# # MacOS (for both x86/x64)
# if(UNIX AND APPLE)

# endif()

# # Linux, BSD, Solaris, Minix (for both x86/x64)
# if(UNIX AND NOT APPLE)   

# endif()

# # Add files to the library
# add_library(${PROJECT_NAME} SHARED ${PROJECT_FILES})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(s21_calculator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET calc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(s21_calculator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(s21_calculator
            ${PROJECT_SOURCES}
        )
    endif()
endif()


# add_executable(s21_calculator, main.cpp)
# # Set version of library
# set_target_properties(${PROJECT_NAME} PROPERTIES 
#                         VERSION ${PROJECT_VERSION}
#                         SOVERSION ${PROJECT_VERSION_MAJOR})

# Link needed libraries
# Qt Library
target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)

# Compile needed definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE QCUSTOMPLOT_COMPILE_LIBRARY)

# Definition which depends on options
# Ex :
# if(EXT_OPT_QCPLIB_XYZ)
#   target_compile_definitions(${PROJECT_NAME} PRIVATE QCPLIB_ENABLE_XYZ)
# endif()

# Directories to includes
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
