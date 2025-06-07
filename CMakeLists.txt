cmake_minimum_required(VERSION 3.16)
project(CalculatorApp)

set(CMAKE_CXX_STANDARD 17)

# Find the Qt6 package
find_package(Qt6 REQUIRED COMPONENTS Widgets Qml)

qt_standard_project_setup()

# Add the executable
add_executable(CalculatorApp main.cpp lib/mainwindow.cpp lib/mainwindow.h)

# Link Qt libraries
target_link_libraries(CalculatorApp PRIVATE Qt6::Widgets Qt6::Qml)
