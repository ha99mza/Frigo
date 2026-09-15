cmake_minimum_required(VERSION 3.21)
project(FrigoHMI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 6.2 (LTS) is the floor because that's what ships on the target board
# (Ubuntu 22.04 aarch64 apt package). qt_standard_project_setup() itself
# was only added in Qt 6.3, so it's called conditionally below.
find_package(Qt6 6.2 REQUIRED COMPONENTS Core Quick QuickControls2 SerialBus)

if(COMMAND qt_standard_project_setup)
    qt_standard_project_setup()
endif()

qt_add_executable(FrigoHMI
    src/main.cpp
    src/canprotocol.h
    src/canprotocol.cpp
    src/frigoconfig.h
    src/frigoconfig.cpp
    src/canbackend.h
    src/canbackend.cpp
    src/cansimulator.h
    src/cansimulator.cpp
    src/frigocontroller.h
    src/frigocontroller.cpp
    src/errorlogmodel.h
    src/errorlogmodel.cpp
    src/historystore.h
    src/historystore.cpp
)

if(POLICY QTP0004)
    qt_policy(SET QTP0004 NEW)
endif()

qt_add_qml_module(FrigoHMI
    URI FrigoHMI
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/TempPage.qml
        qml/HistPage.qml
        qml/AlarmsPage.qml
        qml/SettingsPage.qml
        qml/MaintenancePage.qml
        qml/components/NumPad.qml
        qml/components/TempChart.qml
        qml/components/SettingsRow.qml
    RESOURCES
        resources/qtquickcontrols2.conf
)

target_link_libraries(FrigoHMI PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::SerialBus
)

# Windows: PEAK PCAN-USB uses the Qt SerialBus "peakcan" plugin (PCANBasic.dll
# must be installed on the target machine via the PEAK driver package).
# Linux: uses the built-in "socketcan" plugin against can0 / vcan0 etc.
if(WIN32)
    target_compile_definitions(FrigoHMI PRIVATE FRIGO_PLATFORM_WINDOWS)
elseif(UNIX)
    target_compile_definitions(FrigoHMI PRIVATE FRIGO_PLATFORM_LINUX)
endif()

set_target_properties(FrigoHMI PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

include(GNUInstallDirs)
install(TARGETS FrigoHMI
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
