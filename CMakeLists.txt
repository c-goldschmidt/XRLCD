project (XRLCD)

cmake_minimum_required(VERSION 2.8)

file(GLOB XRLCD_OWN_CPPS "src/*.cpp")
file(GLOB XRLCD_OWN_HS "src/*.h")
file(GLOB XRLCD_OWN_UIS "src/*.ui")

message(STATUS "Sources: ${XRLCD_OWN_CPPS}")
message(STATUS "Headers: ${XRLCD_OWN_HS}")
message(STATUS "UI: ${XRLCD_OWN_UIS}")

set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
include_directories("include")
link_directories("${CMAKE_SOURCE_DIR}/lib/x64/")

ADD_EXECUTABLE(XRLCD ${XRLCD_OWN_CPPS} ${XRLCD_OWN_HS} ${XRLCD_FORMS_HEADERS})
TARGET_LINK_LIBRARIES(XRLCD Qt5::Core "LogitechLCDLib")
