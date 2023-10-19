cmake_minimum_required(VERSION 3.25)

project(QtExmple VERSION 1.0.0 LANGUAGES CXX)

# Qt相关
set(CMAKE_AUTOUIC ON)
# Qt's Meta-Object Compiler
set(CMAKE_AUTOMOC ON)
# Qt资源系统
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# This tells CMake to look up Qt 6, and import the Widgets module.
# There is no point in continuing if CMake cannot locate the module, so we do set the REQUIRED flag to let CMake abort in this case.
# 可以显式的支出Qt的安装路径让CMake能够成功找到Qt。注意QT_INSTALL_PREFIX需要自己填写
list(APPEND CMAKE_PREFIX_PATH /opt/homebrew/Cellar/qt/6.5.1_3/)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# The qt_standard_project_setup command sets project-wide defaults for a typical Qt application.
# Among other things, this command sets the CMAKE_AUTOMOC variable to ON, which instructs CMake to automatically set up rules so that Qt's Meta-Object Compiler (moc) is called transparently, when required.
qt_standard_project_setup()

add_subdirectory(src/app)
add_subdirectory(src/textFinder)